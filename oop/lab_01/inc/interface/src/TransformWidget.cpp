#include "../inc/TransformWidget.h"
#include "../../draw/QtDrawerFactory.h"
#include <QtWidgets/QFileDialog>
#include "../../commands/commands.hpp"
#include "../../draw/QtDrawerFactory.h"
#include <math.h>

TransformWidget::TransformWidget(QWidget *parent)
	: QWidget(parent)
{
	number_cameras = 0;
	number_objects = 0;
	modelBoxLabel = new QLabel(tr("Выбор модели: "), this);
	modelBox = new QComboBox(this);
	
	move_model_label = new QLabel(tr("Перемещение: "), this);
	dx_model_label = new QLabel(tr("OX:"), this);
	dy_model_label = new QLabel(tr("OY:"), this);
	dz_model_label = new QLabel(tr("OZ:"), this);
	
	scale_model_label = new QLabel(tr("Масштабирование: "), this);
	kx_model_label = new QLabel(tr("KX:"), this);
	ky_model_label = new QLabel(tr("KY:"), this);
	kz_model_label = new QLabel(tr("KZ:"), this);
	
	rotate_model_label = new QLabel(tr("Вращение: "), this);
	yz_angle_model_label = new QLabel(tr("OX:"), this);
	xz_angle_model_label = new QLabel(tr("OY:"), this);
	xy_angle_model_label = new QLabel(tr("OZ:"), this);
	
	dx_model_entry = new QLineEdit(this);
	dy_model_entry = new QLineEdit(this);
	dz_model_entry = new QLineEdit(this);
	dx_model_entry->setValidator(new QRegExpValidator(QRegExp(VALID_EXP), this));
	dy_model_entry->setValidator(new QRegExpValidator(QRegExp(VALID_EXP), this));
	dz_model_entry->setValidator(new QRegExpValidator(QRegExp(VALID_EXP), this));
	
	kx_model_entry = new QLineEdit(this);
	ky_model_entry = new QLineEdit(this);
	kz_model_entry = new QLineEdit(this);
	kx_model_entry->setValidator(new QRegExpValidator(QRegExp(VALID_EXP), this));
	ky_model_entry->setValidator(new QRegExpValidator(QRegExp(VALID_EXP), this));
	kz_model_entry->setValidator(new QRegExpValidator(QRegExp(VALID_EXP), this));
	
	yz_model_angle_entry = new QLineEdit(this);
	xz_model_angle_entry = new QLineEdit(this);
	xy_model_angle_entry = new QLineEdit(this);
	yz_model_angle_entry->setValidator(new QRegExpValidator(QRegExp(VALID_EXP), this));
	xz_model_angle_entry->setValidator(new QRegExpValidator(QRegExp(VALID_EXP), this));
	xy_model_angle_entry->setValidator(new QRegExpValidator(QRegExp(VALID_EXP), this));
	
	move_model_btn = new QPushButton("Переместить", this);
	scale_model_btn = new QPushButton("Масштабировать", this);
	rotate_model_btn = new QPushButton("Повернуть", this);
	load_model = new QPushButton("Загрузить фигуру", this);

	load_scene = new QPushButton("Загрузить сцену", this);
	remove_model = new QPushButton("Удалить фигуру", this);
	sceneBoxLabel = new QLabel(tr("Выбор сцены: "), this);
	sceneBox = new QComboBox(this);

	std::string name_str = "Scene_" + std::to_string(++number_scenes);
	QString name = QString::fromStdString(name_str);
	sceneBox->addItem(name);

	connect(move_model_btn, SIGNAL(clicked()), this, SLOT(moveModelClicked()));
	connect(scale_model_btn, SIGNAL(clicked()), this, SLOT(scaleModelClicked()));
	connect(rotate_model_btn, SIGNAL(clicked()), this, SLOT(rotateModelClicked()));
	connect(load_model, SIGNAL(clicked()), this, SLOT(loadModelClicked()));
	connect(remove_model, SIGNAL(clicked()), this, SLOT(removeModelClicked()));
	connect(load_scene, SIGNAL(clicked()), this, SLOT(loadSceneClicked()));

	cameraBoxLabel = new QLabel(tr("Выбор камеры: "), this);
	cameraBox = new QComboBox(this);
	
	move_camera_label = new QLabel(tr("Перемещение: "), this);
	dx_camera_label = new QLabel(tr("OX:"), this);
	dy_camera_label = new QLabel(tr("OY:"), this);
	dz_camera_label = new QLabel(tr("OZ:"), this);
	
	scale_camera_label = new QLabel(tr("Масштабирование: "), this);
	kx_camera_label = new QLabel(tr("KX:"), this);
	ky_camera_label = new QLabel(tr("KY:"), this);
	kz_camera_label = new QLabel(tr("KZ:"), this);
	
	rotate_camera_label = new QLabel(tr("Вращение: "), this);
	yz_angle_camera_label = new QLabel(tr("OX:"), this);
	xz_angle_camera_label = new QLabel(tr("OY:"), this);
	xy_angle_camera_label = new QLabel(tr("OZ:"), this);
	
	dx_camera_entry = new QLineEdit(this);
	dy_camera_entry = new QLineEdit(this);
	dz_camera_entry = new QLineEdit(this);
	dx_camera_entry->setValidator(new QRegExpValidator(QRegExp(VALID_EXP), this));
	dy_camera_entry->setValidator(new QRegExpValidator(QRegExp(VALID_EXP), this));
	dz_camera_entry->setValidator(new QRegExpValidator(QRegExp(VALID_EXP), this));
	
	kx_camera_entry = new QLineEdit(this);
	ky_camera_entry = new QLineEdit(this);
	kz_camera_entry = new QLineEdit(this);
	kx_camera_entry->setValidator(new QRegExpValidator(QRegExp(VALID_EXP), this));
	ky_camera_entry->setValidator(new QRegExpValidator(QRegExp(VALID_EXP), this));
	kz_camera_entry->setValidator(new QRegExpValidator(QRegExp(VALID_EXP), this));
	
	yz_camera_angle_entry = new QLineEdit(this);
	xz_camera_angle_entry = new QLineEdit(this);
	xy_camera_angle_entry = new QLineEdit(this);
	yz_camera_angle_entry->setValidator(new QRegExpValidator(QRegExp(VALID_EXP), this));
	xz_camera_angle_entry->setValidator(new QRegExpValidator(QRegExp(VALID_EXP), this));
	xy_camera_angle_entry->setValidator(new QRegExpValidator(QRegExp(VALID_EXP), this));
	
	move_camera_btn = new QPushButton("Переместить", this);
	scale_camera_btn = new QPushButton("Масштабировать", this);
	rotate_camera_btn = new QPushButton("Повернуть", this);
	add_camera = new QPushButton("Добавить камеру", this);
	remove_camera = new QPushButton("Удалить камеру", this);

	connect(move_camera_btn, SIGNAL(clicked()), this, SLOT(moveCameraClicked()));
	connect(scale_camera_btn, SIGNAL(clicked()), this, SLOT(scaleCameraClicked()));
	connect(rotate_camera_btn, SIGNAL(clicked()), this, SLOT(rotateCameraClicked()));
	connect(add_camera, SIGNAL(clicked()), this, SLOT(addCameraClicked()));
	connect(remove_camera, SIGNAL(clicked()), this, SLOT(removeCameraClicked()));

	graphicsView = new QGraphicsView(this);
    scene = new QGraphicsScene(this);
    graphicsView->setScene(scene);
    graphicsView->setAlignment(Qt::AlignTop | Qt::AlignLeft);

    scene->setSceneRect(0, 0, 700, 600);

    std::shared_ptr<DrawerFactory> factory(new QtDrawerFactory(scene));
    drawer = factory->createDrawer();

	facade = std::make_shared<Facade>(Facade());

	connect(cameraBox, SIGNAL(currentIndexChanged(int)), this, SLOT(cameraChanged(int)));
	connect(modelBox, SIGNAL(currentIndexChanged(int)), this, SLOT(modelChanged(int)));
	connect(sceneBox, SIGNAL(currentIndexChanged(int)), this, SLOT(sceneChanged(int)));

	mainLayout = new QGridLayout;
	mainLayout->setSizeConstraint(QLayout::SetFixedSize);
	
	mainLayout->addWidget(modelBoxLabel, 0, 0);
	mainLayout->addWidget(modelBox, 0, 1, 1, 3);

	mainLayout->addWidget(load_model, 0, 5);
	mainLayout->addWidget(remove_model, 0, 6);

	mainLayout->addWidget(move_model_label, 1, 1, 1, 5);

	mainLayout->addWidget(dx_model_label, 2, 0);
	mainLayout->addWidget(dx_model_entry, 2, 1);
	mainLayout->addWidget(dy_model_label, 2, 2);
	mainLayout->addWidget(dy_model_entry, 2, 3);
	mainLayout->addWidget(dz_model_label, 2, 4);
	mainLayout->addWidget(dz_model_entry, 2, 5);

	mainLayout->addWidget(move_model_btn, 3, 5);

	mainLayout->addWidget(scale_model_label, 4, 1, 1, 5);

	mainLayout->addWidget(kx_model_label, 5, 0);
	mainLayout->addWidget(kx_model_entry, 5, 1);
	mainLayout->addWidget(ky_model_label, 5, 2);
	mainLayout->addWidget(ky_model_entry, 5, 3);
	mainLayout->addWidget(kz_model_label, 5, 4);
	mainLayout->addWidget(kz_model_entry, 5, 5);

	mainLayout->addWidget(scale_model_btn, 6, 5);

	mainLayout->addWidget(rotate_model_label, 7, 1, 1, 5);

	mainLayout->addWidget(yz_angle_model_label, 8, 0);
	mainLayout->addWidget(yz_model_angle_entry, 8, 1);
	mainLayout->addWidget(xz_angle_model_label, 8, 2);
	mainLayout->addWidget(xz_model_angle_entry, 8, 3);
	mainLayout->addWidget(xy_angle_model_label, 8, 4);
	mainLayout->addWidget(xy_model_angle_entry, 8, 5);

	mainLayout->addWidget(rotate_model_btn, 9, 5);

	mainLayout->addWidget(cameraBoxLabel, 11, 0);
	mainLayout->addWidget(cameraBox, 11, 1, 1, 3);

	mainLayout->addWidget(add_camera, 11, 5);
	mainLayout->addWidget(remove_camera, 11, 6);

	mainLayout->addWidget(move_camera_label, 12, 1, 1, 5);

	mainLayout->addWidget(dx_camera_label, 13, 0);
	mainLayout->addWidget(dx_camera_entry, 13, 1);
	mainLayout->addWidget(dy_camera_label, 13, 2);
	mainLayout->addWidget(dy_camera_entry, 13, 3);
	mainLayout->addWidget(dz_camera_label, 13, 4);
	mainLayout->addWidget(dz_camera_entry, 13, 5);

	mainLayout->addWidget(move_camera_btn, 14, 5);

	mainLayout->addWidget(scale_camera_label, 15, 1, 1, 5);

	mainLayout->addWidget(kx_camera_label, 16, 0);
	mainLayout->addWidget(kx_camera_entry, 16, 1);
	mainLayout->addWidget(ky_camera_label, 16, 2);
	mainLayout->addWidget(ky_camera_entry, 16, 3);
	mainLayout->addWidget(kz_camera_label, 16, 4);
	mainLayout->addWidget(kz_camera_entry, 16, 5);

	mainLayout->addWidget(scale_camera_btn, 17, 5);

	mainLayout->addWidget(rotate_camera_label, 18, 1, 1, 5);

	mainLayout->addWidget(yz_angle_camera_label, 19, 0);
	mainLayout->addWidget(yz_camera_angle_entry, 19, 1);
	mainLayout->addWidget(xz_angle_camera_label, 19, 2);
	mainLayout->addWidget(xz_camera_angle_entry, 19, 3);
	mainLayout->addWidget(xy_angle_camera_label, 19, 4);
	mainLayout->addWidget(xy_camera_angle_entry, 19, 5);

	mainLayout->addWidget(rotate_camera_btn, 20, 5);

	mainLayout->addWidget(sceneBoxLabel, 22, 0);
	mainLayout->addWidget(sceneBox, 22, 1, 1, 3);
	mainLayout->addWidget(load_scene, 22, 5);
	// graphicsView->setGeometry(0, 0, 700, 600);
	mainLayout->addWidget(graphicsView, 0, 7, 30, 25);
	setLayout(mainLayout);

	setWindowTitle(tr("3D application"));

}

TransformWidget::~TransformWidget()
{
}

void TransformWidget::drawScene() 
{
	std::shared_ptr<DrawManager> draw = DrawManagerCreator().getManager();
	draw->setDrawer(QtDrawerFactory(scene).createDrawer());
	std::shared_ptr<DrawCommand> drawCommand(new DrawCommand(draw, &DrawManager::drawModel));
	facade->execute(drawCommand);
}


void TransformWidget::loadModelClicked()
{
	QString file = QFileDialog::getOpenFileName(this, QString::fromUtf8("Открыть файл"), QDir::currentPath(), "text files (*.txt)");
	if (file.isEmpty())
		return;

	std::string name_str = "Model_" + std::to_string(++number_objects);
	QString name = QString::fromStdString(name_str);
	std::string filename = file.toLocal8Bit().constData();
	try {
		std::shared_ptr<LoadManager> manager = LoadManagerCreator().getManager();
		std::shared_ptr<LoadCommand> loadCommand(new LoadCommand(manager, &LoadManager::loadObject, ObjectType::MODEL, filename));
		facade->execute(loadCommand);
		modelBox->addItem(name);
		drawScene();
	} catch (BaseException& ex) {
		QMessageBox::warning(this, "Error", QString(ex.what()));
	}
}

void TransformWidget::loadSceneClicked()
{
	QString file = QFileDialog::getOpenFileName(this, QString::fromUtf8("Открыть файл"), QDir::currentPath(), "text files (*.txt)");
	if (file.isEmpty())
		return;
	std::string filename = file.toLocal8Bit().constData();
	try {
		std::string name_str = "Scene_" + std::to_string(++number_scenes);
		QString name = QString::fromStdString(name_str);
		sceneBox->addItem(name);
		std::shared_ptr<LoadManager> manager = LoadManagerCreator().getManager();
		std::shared_ptr<LoadCommand> loadCommand(new LoadCommand(manager, &LoadManager::loadObject, ObjectType::COMPOSITE, filename));
		facade->execute(loadCommand);
		std::shared_ptr<ObjectManager> obj_manager = ObjectManagerCreator().getManager();
		number_objects = 0;
		std::shared_ptr<GetAmountCommand> getAmount(new GetAmountCommand(obj_manager, &ObjectManager::getObjectsAmount, ObjectType::MODEL, number_objects));
		facade->execute(getAmount);
		modelBox->clear();
		for (int i = 0; i < number_objects; i++)
		{
			std::string name_str = "Model_" + std::to_string(i);
			QString name = QString::fromStdString(name_str);
			modelBox->addItem(name);
		}
		number_cameras = 0;
		getAmount.reset(new GetAmountCommand(obj_manager, &ObjectManager::getObjectsAmount, ObjectType::CAMERA, number_cameras));
		facade->execute(getAmount);
		cameraBox->clear();
		for (int i = 0; i < number_cameras; i++)
		{
			std::string name_str = "camera_" + std::to_string(i);
			QString name = QString::fromStdString(name_str);
			cameraBox->addItem(name);
		}
		drawScene();
	} catch (BaseException& ex) {
		QMessageBox::warning(this, "Error", QString(ex.what()));
	}
}

void TransformWidget::removeModelClicked()
{
	try {
		std::shared_ptr<ObjectManager> manager = ObjectManagerCreator().getManager();
		std::shared_ptr<RemoveObjectCommand> removeCommand(new RemoveObjectCommand(manager, &ObjectManager::removeObject, ObjectType::MODEL));
		facade->execute(removeCommand);
		modelBox->removeItem(modelBox->currentIndex());
		number_objects--;
		drawScene();
	} catch (BaseException& ex) {
		QMessageBox::warning(this, "Error", QString(ex.what()));
	}
}

void TransformWidget::moveModelClicked()
{
	Vector<double> params = Vector<double>(3);
	int i = 0;
	bool dx_empty = dx_model_entry->text().isEmpty();
	bool dy_empty = dy_model_entry->text().isEmpty();
	bool dz_empty = dz_model_entry->text().isEmpty();

	params[i] = (dx_empty) ? 0 : dx_model_entry->text().toDouble();
	i++;
	params[i] = (dy_empty) ? 0 : dy_model_entry->text().toDouble();
	i++;
	params[i] = (dz_empty) ? 0 : dz_model_entry->text().toDouble();
	i++;

	try {
		std::shared_ptr<TransformManager> manager = TransformManagerCreator().getManager();
		std::shared_ptr<MoveCommand> move(new MoveCommand(manager, &TransformManager::move, ObjectType::MODEL, params));
		facade->execute(move);
		drawScene();
	} catch (BaseException &ex) {
		QMessageBox::warning(this, "Error", QString(ex.what()));
	}
}

void TransformWidget::scaleModelClicked()
{
	Vector<double> params = Vector<double>(3);
	int i = 0;
	bool dx_empty = kx_model_entry->text().isEmpty();
	bool dy_empty = ky_model_entry->text().isEmpty();
	bool dz_empty = kz_model_entry->text().isEmpty();

	params[i] = (dx_empty) ? 1 : kx_model_entry->text().toDouble();
	i++;
	params[i] = (dy_empty) ? 1 : ky_model_entry->text().toDouble();
	i++;
	params[i] = (dz_empty) ? 1 : kz_model_entry->text().toDouble();
	i++;

	try {
		std::shared_ptr<TransformManager> manager = TransformManagerCreator().getManager();
		std::shared_ptr<ScaleCommand> scale(new ScaleCommand(manager, &TransformManager::scale, ObjectType::MODEL, params));
		facade->execute(scale);
		drawScene();
	} catch (BaseException &ex) {
		QMessageBox::warning(this, "Error", QString(ex.what()));
	}
}

void TransformWidget::rotateModelClicked()
{
	Vector<double> params = Vector<double>(3);
	int i = 0;
	bool dx_empty = yz_model_angle_entry->text().isEmpty();
	bool dy_empty = xz_model_angle_entry->text().isEmpty();
	bool dz_empty = xy_model_angle_entry->text().isEmpty();

	params[i] = (dx_empty) ? 0 : yz_model_angle_entry->text().toDouble() / 180 * M_PI;
	i++;
	params[i] = (dy_empty) ? 0 : xz_model_angle_entry->text().toDouble() / 180 * M_PI;
	i++;
	params[i] = (dz_empty) ? 0 : xy_model_angle_entry->text().toDouble() / 180 * M_PI;
	i++;

	try {
		std::shared_ptr<TransformManager> manager = TransformManagerCreator().getManager();
		std::shared_ptr<RotateCommand> move(new RotateCommand(manager, &TransformManager::rotate, ObjectType::MODEL, params));
		facade->execute(move);
		drawScene();
	} catch (BaseException &ex) {
		QMessageBox::warning(this, "Error", QString(ex.what()));
	}
}

void TransformWidget::addCameraClicked()
{
	try {
		std::shared_ptr<ObjectManager> manager = ObjectManagerCreator().getManager();
		std::shared_ptr<AddObjectCommand> addCommand(new AddObjectCommand(manager, &ObjectManager::addObject, ObjectType::CAMERA));
		facade->execute(addCommand);
		std::string name_str = "camera_" + std::to_string(++number_cameras);
		QString name = QString::fromStdString(name_str);
		cameraBox->addItem(name);
		// drawScene();
	} catch (BaseException& ex) {
		QMessageBox::warning(this, "Error", QString(ex.what()));
	}
}

void TransformWidget::removeCameraClicked()
{
	try {
		std::shared_ptr<ObjectManager> manager = ObjectManagerCreator().getManager();
		std::shared_ptr<RemoveObjectCommand> removeCommand(new RemoveObjectCommand(manager, &ObjectManager::removeObject, ObjectType::CAMERA));
		facade->execute(removeCommand);
		cameraBox->removeItem(cameraBox->currentIndex());
		number_cameras--;
		drawScene();
	} catch (BaseException& ex) {
		QMessageBox::warning(this, "Error", QString(ex.what()));
	}
}

void TransformWidget::moveCameraClicked()
{
	Vector<double> params = Vector<double>(3);
	int i = 0;
	bool dx_empty = dx_camera_entry->text().isEmpty();
	bool dy_empty = dy_camera_entry->text().isEmpty();
	bool dz_empty = dz_camera_entry->text().isEmpty();

	params[i] = (dx_empty) ? 0 : dx_camera_entry->text().toDouble();
	i++;
	params[i] = (dy_empty) ? 0 : dy_camera_entry->text().toDouble();
	i++;
	params[i] = (dz_empty) ? 0 : dz_camera_entry->text().toDouble();
	i++;

	try {
		std::shared_ptr<TransformManager> manager = TransformManagerCreator().getManager();
		std::shared_ptr<MoveCommand> move(new MoveCommand(manager, &TransformManager::move, ObjectType::CAMERA, params));
		facade->execute(move);
		drawScene();
	} catch (BaseException &ex) {
		QMessageBox::warning(this, "Error", QString(ex.what()));
	}
}

void TransformWidget::scaleCameraClicked()
{
	Vector<double> params = Vector<double>(3);
	int i = 0;
	bool dx_empty = kx_camera_entry->text().isEmpty();
	bool dy_empty = ky_camera_entry->text().isEmpty();
	bool dz_empty = kz_camera_entry->text().isEmpty();

	params[i] = (dx_empty) ? 1 : kx_camera_entry->text().toDouble();
	i++;
	params[i] = (dy_empty) ? 1 : ky_camera_entry->text().toDouble();
	i++;
	params[i] = (dz_empty) ? 1 : kz_camera_entry->text().toDouble();
	i++;

	try {
		std::shared_ptr<TransformManager> manager = TransformManagerCreator().getManager();
		std::shared_ptr<ScaleCommand> scale(new ScaleCommand(manager, &TransformManager::scale, ObjectType::CAMERA, params));
		facade->execute(scale);
		drawScene();
	} catch (BaseException &ex) {
		QMessageBox::warning(this, "Error", QString(ex.what()));
	}
}

void TransformWidget::rotateCameraClicked()
{

	Vector<double> params = Vector<double>(3);
	int i = 0;
	bool dx_empty = yz_camera_angle_entry->text().isEmpty();
	bool dy_empty = xz_camera_angle_entry->text().isEmpty();
	bool dz_empty = xz_camera_angle_entry->text().isEmpty();

	params[i] = (dx_empty) ? 0 : yz_camera_angle_entry->text().toDouble();
	i++;
	params[i] = (dy_empty) ? 0 : xz_camera_angle_entry->text().toDouble();
	i++;
	params[i] = (dz_empty) ? 0 : xy_camera_angle_entry->text().toDouble();
	i++;

	try {
		std::shared_ptr<TransformManager> manager = TransformManagerCreator().getManager();
		std::shared_ptr<RotateCommand> move(new RotateCommand(manager, &TransformManager::rotate, ObjectType::CAMERA, params));
		facade->execute(move);
		drawScene();
	} catch (BaseException &ex) {
		QMessageBox::warning(this, "Error", QString(ex.what()));
	}
}

void TransformWidget::cameraChanged(int index)
{
	try {
		std::shared_ptr<ObjectManager> manager = ObjectManagerCreator().getManager();
		std::shared_ptr<ChangeObjectCommand> command(new ChangeObjectCommand(manager, &ObjectManager::changeCurrentObject, ObjectType::CAMERA, index));
		facade->execute(command);
		drawScene();
	} catch (BaseException &ex) {
		QMessageBox::warning(this, "Error", QString(ex.what()));
	}
}

void TransformWidget::sceneChanged(int index)
{
	try {
		std::shared_ptr<ObjectManager> manager = ObjectManagerCreator().getManager();
		std::shared_ptr<ChangeObjectCommand> command(new ChangeObjectCommand(manager, &ObjectManager::changeCurrentObject, ObjectType::COMPOSITE, index));
		facade->execute(command);
		number_cameras = 0;
		cameraBox->clear();
		std::shared_ptr<GetAmountCommand> command_count(new GetAmountCommand(manager, &ObjectManager::getObjectsAmount, ObjectType::CAMERA, number_cameras));
		facade->execute(command_count);
		for (int i = 0; i < number_cameras; i++)
		{
			std::string name_str = "Camera_" + std::to_string(i);
			QString name = QString::fromStdString(name_str);
			cameraBox->addItem(name);
		}
		modelBox->clear();
		number_objects = 0;
		command_count.reset(new GetAmountCommand(manager, &ObjectManager::getObjectsAmount, ObjectType::MODEL, number_objects));
		facade->execute(command_count);
		for (int i = 0; i < number_objects; i++)
		{
			std::string name_str = "Model_" + std::to_string(i);
			QString name = QString::fromStdString(name_str);
			modelBox->addItem(name);
		}
		drawScene();
	} catch (BaseException &ex) {
		QMessageBox::warning(this, "Error", QString(ex.what()));
	}
}

void TransformWidget::modelChanged(int index)
{
	try {
		std::shared_ptr<ObjectManager> manager = ObjectManagerCreator().getManager();
		std::shared_ptr<ChangeObjectCommand> command(new ChangeObjectCommand(manager, &ObjectManager::changeCurrentObject, ObjectType::MODEL, index));
		facade->execute(command);
	} catch (BaseException &ex) {
		QMessageBox::warning(this, "Error", QString(ex.what()));
	}
}
