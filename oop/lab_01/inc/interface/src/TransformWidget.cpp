#include "../inc/TransformWidget.h"
#include "../../draw/QtDrawerFactory.h"

TransformWidget::TransformWidget(QWidget *parent)
	: QWidget(parent)
{
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
	remove_model = new QPushButton("Удалить фигуру", this);

	connect(move_model_btn, SIGNAL(clicked()), this, SLOT(moveModelClicked()));
	connect(scale_model_btn, SIGNAL(clicked()), this, SLOT(scaleModelClicked()));
	connect(rotate_model_btn, SIGNAL(clicked()), this, SLOT(rotateModelClicked()));
	connect(load_model, SIGNAL(clicked()), this, SLOT(loadModelClicked()));
	connect(remove_model, SIGNAL(clicked()), this, SLOT(removeModeClicked()));

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

	mainLayout->addWidget(graphicsView, 0, 7, 25, 15);
	setLayout(mainLayout);

	setWindowTitle(tr("3D application"));

    scene = new QGraphicsScene(this);
    graphicsView->setScene(scene);
    graphicsView->setAlignment(Qt::AlignTop | Qt::AlignLeft);

    auto rcontent = graphicsView->contentsRect();
    scene->setSceneRect(0, 0, rcontent.width(), rcontent.height());

    std::shared_ptr<DrawerFactory> factory(new QtDrawerFactory(scene));
    drawer = factory->createDrawer();

	facade = std::make_shared<Facade>(Facade());

	connect(cameraBox, QOverload<int>::of(&QComboBox::currentIndexChanged), this, SLOT(cameraChanged()));
	connect(modelBox, QOverload<int>::of(&QComboBox::currentIndexChanged), this, SLOT(modelChanged()));

}

TransformWidget::~TransformWidget()
{
}
