#ifndef SETUP_HPP
#define SETUP_HPP

#include <vector>
#include "voronoi_tools.hpp"
#include "random_thijs.hpp"
#include "parameters.hpp"
#include "simulation.hpp"
#include "voronoi.hpp"

namespace setup {
  template <typename NODE>
  void setup_voronoi(std::vector< std::vector< voronoi_point > >& all_polys,
                     grid_type used_grid_type,
                     size_t num_cells,
                     size_t sq_size,
                     rnd_t& rndgen,
                     std::vector<NODE>& world) {

    // std::cout << "Generating centre points\n";
    std::vector< voronoi_point > v(num_cells);


    // we make regular grid
    for(size_t i = 0; i < num_cells; ++i) {

        float x, y;

        if (used_grid_type == grid_type::hexagonal) {
            x = i % sq_size;
            y = i / sq_size;
            if ((i / sq_size) % 2 == 0) x += 0.5f;
          } else {
            x = rndgen.uniform() * sq_size;
            y = rndgen.uniform() * sq_size;
          }

        v[i] = voronoi_point(x, y);
      }

    cinekine::voronoi::Sites sites;
    // << "converting centre points to vertices\n";
    for(auto i : v) {
        cinekine::voronoi::Vertex temp_vertex(i.x_, i.y_);
        sites.push_back(temp_vertex);
      }

    // std::cout << "creating voronoi graph\n";
    cinekine::voronoi::Graph graph = cinekine::voronoi::build(std::move(sites), sq_size, sq_size);

    std::vector< std::vector< voronoi_edge > > all_edges(world.size());

    // std::cout << "Ready to build world\n";
    // std::cout << "collecting all edges\n";
    for(const auto& cell : graph.cells()) {

        size_t site_index = static_cast<size_t>(cell.site);

        cinekine::voronoi::Site focal_site = graph.sites()[site_index];

        world[site_index].x_ = focal_site.x;
        world[site_index].y_ = focal_site.y;

        for(const auto& edge : cell.halfEdges) {
            cinekine::voronoi::Edge focal_edge = graph.edges()[edge.edge];
            voronoi_point start(focal_edge.p0.x, focal_edge.p0.y);
            voronoi_point end(  focal_edge.p1.x, focal_edge.p1.y);

            voronoi_edge local_edge(start, end, focal_edge.leftSite, focal_edge.rightSite);

            if(local_edge.calc_dist() > 1e-2) {
                all_edges[site_index].push_back(local_edge);
              }
          }
      }

    // std::cout << "implementing all edges\n";
    for(auto i : all_edges) {
        for(auto edge : i) {
            size_t left  = edge.left;
            size_t right = edge.right;

            if(left < world.size() && right < world.size()) {
                world[left].template add_neighbor<NODE>(world, right);
                world[right].template add_neighbor<NODE>(world, left);
              }
          }
      }

    // std::cout << "clean edges and add polies for plotting\n";
    for(size_t i = 0; i < num_cells; ++i) {
        std::vector< voronoi_point > poly = voronoi_tools::clean_edges(all_edges[i], i);
        all_polys.push_back(poly);
      }
  }


  template <typename NODE>
  void initialize_network(std::vector< std::vector< voronoi_point > >& all_polys,
                          grid_type used_grid_type,
                          simulation<NODE>& sim,
                          const Param& parameters) {
    // initialize default.
    for(size_t i = 0; i < 4; ++i) {
        sim.growth_prob[i] = binned_distribution(sim.sq_size, sim.num_cells);
        sim.death_prob[i] = binned_distribution(sim.sq_size, sim.num_cells);
    }

    for(auto& i : sim.world) {
        i.prob_normal_infected = parameters.prob_normal_infection;
      }

    if(parameters.use_voronoi_grid == false) {
        for(auto& i : sim.world) {
            i.update_neighbors(sim.world, sim.sq_size);
            sim.change_cell_type(i.pos, empty);
          }
      }
    if(parameters.use_voronoi_grid == true) {

        setup_voronoi(all_polys, used_grid_type,
                      sim.num_cells, sim.sq_size, sim.rndgen, sim.world);
        for(size_t i = 0; i < sim.num_cells; ++i) {
            sim.world[i].inv_num_neighbors = 1.f / sim.world[i].neighbors.size();
            sim.update_growth_prob(i);
            sim.update_death_prob(i);
          }
      }

    if(parameters.start_setup == grow || parameters.start_setup == converge) {
         sim.add_cells(normal);
        for(size_t i = 0; i < sim.num_cells; ++i) {
            sim.update_growth_prob(i);
            sim.update_death_prob(i);
          }
      }

    if(parameters.start_setup == full) {
        sim.initialize_full();
    }

    for(size_t i = 0; i < sim.growth_prob.size(); ++i) {
        sim.growth_prob[i].update_all();
        sim.death_prob[i].update_all();
    }
  }
}

#endif // SETUP_HPP
