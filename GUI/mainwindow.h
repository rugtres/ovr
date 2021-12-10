#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "qcustomplot.h"
#include <QMainWindow>
#include <QPaintEvent>
#include <QPainter>

#include "../Simulation/simulation.hpp"
#include "../Simulation/voronoi_tools.hpp"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

enum display_color {cells, inflammation_factor, added_death_rate,
                    normal_rate, normal_death_rate,
                    cancer_rate, cancer_death_rate,
                    infected_rate, resistant_rate,
                    dominant_rate};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
     ~MainWindow();

    void update_image();

    void update_image(const std::array< binned_distribution, 4 > & growth_rate);


    void display_voronoi(); // cell coloring
    void display_voronoi(const binned_distribution& growth_rate,
                         cell_type focal_cell_type); // growth rate coloring
    void display_voronoi(const std::array< binned_distribution, 4 > & growth_rate); // dominant growth rate coloring

    void display_regular(bool using_3d); // cell type coloring
    void display_regular(const binned_distribution& growth_rate,
                         cell_type focal_cell_type,
                         bool using_3d); // growth rate coloring
    void display_regular(const std::array< binned_distribution, 4 > & growth_rate,
                         bool using_3d); // dominant growth rate coloring
    void display_regular_death_rate(const binned_distribution& death_rate,
                            cell_type focal_cell_type,
                                    bool using_3d);

    void update_parameters(Param& p);
    void set_resolution(int width, int height);
    void set_pixel(int x, int y, const QColor& col);
    void update_polygons(const std::vector< std::vector< voronoi_point > >& all_edges);

    void update_plot(double t, const std::array<size_t, 5>& cell_numbers);
    void setup_simulation();
    void obtain_equilibrium();
    void update_display();

    void update_3d_gui();

private slots:
    void on_btn_start_clicked();

    void on_btn_stop_clicked();

    void on_speed_slider_actionTriggered(int action);

    void on_drpdwnbox_display_activated(int index);

    void on_btn_setup_clicked();

    void on_btn_add_virus_clicked();

    void on_btn_use_3d_clicked();

    void on_box_death_cancer_resistant_valueChanged(double arg1);

    void on_box_birth_infected_valueChanged(double arg1);

    void on_box_death_infected_valueChanged(double arg1);

    void on_box_birth_cancer_resistant_valueChanged(double arg1);

    void on_box_grid_type_currentIndexChanged(int index);

    void on_box_sq_num_cells_valueChanged(double arg1);

    void on_box_birth_normal_valueChanged(double arg1);

    void on_box_death_normal_valueChanged(double arg1);

    void on_box_birth_cancer_valueChanged(double arg1);

    void on_box_death_cancer_valueChanged(double arg1);

    void on_box_maxtime_valueChanged(int arg1);

    void on_box_cancer_time_valueChanged(int arg1);

    void on_box_virus_time_valueChanged(int arg1);

    void on_box_prob_normal_infection_valueChanged(double arg1);

    void on_box_freq_resistant_cancer_valueChanged(double arg1);

    void on_box_percent_infected_valueChanged(double arg1);

    void on_box_sq_num_pixels_valueChanged(double arg1);

    void on_box_normal_cells_valueChanged(int arg1);

    void on_box_cancer_cells_valueChanged(int arg1);

    void on_box_distance_infection_death_valueChanged(double arg1);

    void on_box_prob_infection_death_valueChanged(double arg1);

    void on_box_infection_routine_currentIndexChanged(int index);

    void on_depth_slider_actionTriggered(int action);

    void on_depth_slider_sliderMoved(int position);

    void on_box_start_setup_activated(int index);

private:
    Ui::MainWindow *ui;
    QImage image_;

    size_t row_size;
    size_t col_size;
    float factor_x;
    float factor_y;

    bool using_3d;
    bool basic_setup_done;

    display_color focal_display_type;

    QVector<double> x_t;
    QVector<double> y_n;
    QVector<double> y_c;
    QVector<double> y_i;
    QVector<double> y_r;

    std::vector< QPolygonF > polygons;

    bool is_running;
    bool is_paused;
    int update_speed;

    grid_type grid_type;

    Param all_parameters;

    std::unique_ptr<simulation> sim;

    std::vector< QColor > colorz;
};


#endif // MAINWINDOW_H
