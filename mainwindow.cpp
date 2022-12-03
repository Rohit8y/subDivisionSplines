#include "mainwindow.h"

#include "ui_mainwindow.h"

/**
 * @brief MainWindow::MainWindow Creates a new Main Window UI.
 * @param parent Qt parent widget.
 */
MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  qDebug() << "✓✓ MainWindow constructor";
  ui->setupUi(this);

  // Set some default UI values
  Settings& settings = ui->mainView->settings;
  ui->controlNetCheckBox->setChecked(settings.showNet);
  ui->subdivCurveCheckBox->setChecked(settings.showSubdivisionCurve);
  ui->subdivCurveCheckBox->setChecked(settings.showCombCurve);
  ui->subdivCurveCheckBox->setChecked(settings.showTessellation);
  ui->subdivCurveCheckBox->setChecked(settings.showInfluence);




  // Input restrictions for the Mask
  ui->subdivMask->setValidator(new QRegularExpressionValidator(
      QRegularExpression("(-?\\d+\\s)+(-?\\d+\\s?)")));

  // Initialise mask
  ui->mainView->subCurve.setMask(ui->subdivMask->text());
}

/**
 * @brief MainWindow::~MainWindow Deconstructs the main window.
 */
MainWindow::~MainWindow() {
  qDebug() << "✗✗ MainWindow destructor";
  delete ui;
}

// Don't worry about adding documentation for the UI-related functions.

void MainWindow::on_controlNetCheckBox_toggled(bool checked) {
  ui->mainView->settings.showNet = checked;
  ui->mainView->update();
}

void MainWindow::on_subdivCurveCheckBox_toggled(bool checked) {
  // Call the function to get curveCoords initiated;
 // ui->mainView->subCurve.presetCurve();
  ui->mainView->settings.showSubdivisionCurve = checked;
  ui->mainView->update();
  ui->mainView->updateBuffers();

}

void MainWindow::on_curvatureCombCheckBox_toggled(bool checked)
{
    qDebug() << "curvature comb activated";
    ui->mainView->settings.showCombCurve = checked;
    ui->mainView->update();
    ui->mainView->updateBuffers();

}

void MainWindow::on_tessellationCheckBox_toggled(bool checked)
{
    qDebug() << "Tessellation activated";

    ui->mainView->settings.showTessellation = checked;
    ui->mainView->update();
    ui->mainView->updateBuffers();


}

void MainWindow::on_netPresets_currentIndexChanged(int index) {
  if (ui->mainView->isValid()) {
    ui->mainView->subCurve.presetNet(index);
   // ui->mainView->subCurve.presetCurve();
    ui->mainView->subCurve.someSubdivideFunction(steps);


  }
  ui->mainView->updateBuffers();
}

void MainWindow::on_subdivMask_returnPressed() {
  ui->mainView->subCurve.setMask(ui->subdivMask->text());
  ui->mainView->subCurve.someSubdivideFunction(steps);

  ui->mainView->update();
  ui->mainView->updateBuffers();

}

void MainWindow::on_subdivSteps_valueChanged(int numSteps) {

    // Calling our subdivide function.
    if (ui->mainView->isValid()) {
        ui->mainView->subCurve.someSubdivideFunction(numSteps);
        steps=numSteps;
    }
   ui->mainView->updateBuffers();
}

void MainWindow::on_noIsoline_valueChanged(int noIso)
{
    ui->mainView->settings.no_Isolines = static_cast< float >(noIso);
    ui->mainView->update();
    ui->mainView->updateBuffers();}


void MainWindow::on_noSplit_valueChanged(int noSpl)
{
    ui->mainView->settings.no_Split = static_cast< float >(noSpl);
    ui->mainView->update();
    ui->mainView->updateBuffers();}


void MainWindow::on_noIsoline_textChanged(const QString &arg1)
{

}

void MainWindow::on_checkBox_toggled(bool checked){

}

void MainWindow::on_highlight_toggled(bool checked)
{
    ui->mainView->settings.showInfluence = checked;
    ui->mainView->subCurve.highlightInfluence(ui->mainView->settings.selectedPointSub);
    ui->mainView->update();
    ui->mainView->updateBuffers();
}

