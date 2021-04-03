#include "../inc/TransformWidget.h"

TransformWidget::TransformWidget(QWidget *parent)
	: QWidget(parent)
{
	view = new FigureView(this, this->params);

	move_label = new QLabel(tr("Смещение вдоль осей координат"), this);
	dx_label = new QLabel(tr("Вдоль OX:"), this);
	dy_label = new QLabel(tr("Вдоль OY:"), this);
	dz_label = new QLabel(tr("Вдоль OZ:"), this);
	
	scale_label = new QLabel(tr("Масштабирование относительно центра фигуры"), this);
	kx_label = new QLabel(tr("Вдоль OX:"), this);
	ky_label = new QLabel(tr("Вдоль OY:"), this);
	kz_label = new QLabel(tr("Вдоль OZ:"), this);
	
	rotate_label = new QLabel(tr("Вращение относительно центра фигуры (в углах)"), this);
	yz_angle_label = new QLabel(tr("Поворот относительно OX:"), this);
	xz_angle_label = new QLabel(tr("Поворот относительно OY:"), this);
	xy_angle_label = new QLabel(tr("Поворот относительно OZ:"), this);
	
	dx_entry = new QLineEdit(this);
	dy_entry = new QLineEdit(this);
	dz_entry = new QLineEdit(this);
	dx_entry->setValidator(new QRegExpValidator(QRegExp(VALID_EXP), this));
	dy_entry->setValidator(new QRegExpValidator(QRegExp(VALID_EXP), this));
	dz_entry->setValidator(new QRegExpValidator(QRegExp(VALID_EXP), this));
	
	kx_entry = new QLineEdit(this);
	ky_entry = new QLineEdit(this);
	kz_entry = new QLineEdit(this);
	kx_entry->setValidator(new QRegExpValidator(QRegExp(VALID_EXP), this));
	ky_entry->setValidator(new QRegExpValidator(QRegExp(VALID_EXP), this));
	kz_entry->setValidator(new QRegExpValidator(QRegExp(VALID_EXP), this));
	
	yz_angle_entry = new QLineEdit(this);
	xz_angle_entry = new QLineEdit(this);
	xy_angle_entry = new QLineEdit(this);
	
	yz_angle_entry->setValidator(new QRegExpValidator(QRegExp(VALID_EXP), this));
	xz_angle_entry->setValidator(new QRegExpValidator(QRegExp(VALID_EXP), this));
	xy_angle_entry->setValidator(new QRegExpValidator(QRegExp(VALID_EXP), this));
	
	move_btn = new QPushButton("Переместить", this);
	scale_btn = new QPushButton("Масштабировать", this);
	rotate_btn = new QPushButton("Повернуть", this);
	load_from_btn = new QPushButton("Загрузить фигуру", this);
	load_to_file_btn = new QPushButton("Сохранить фигуру", this);

	connect(move_btn, SIGNAL(clicked()), this, SLOT(moveClicked()));
	connect(scale_btn, SIGNAL(clicked()), this, SLOT(scaleClicked()));
	connect(rotate_btn, SIGNAL(clicked()), this, SLOT(rotateClicked()));
	connect(load_from_btn, SIGNAL(clicked()), this, SLOT(loadFromClicked()));
	connect(load_to_file_btn, SIGNAL(clicked()), this, SLOT(loadToClicked()));

	file_label = new QLabel("Имя файла для считывания/сохранения модели", this);
	file_entry = new QLineEdit(this);

	mainLayout = new QGridLayout;
	mainLayout->setSizeConstraint(QLayout::SetFixedSize);
	
	mainLayout->addWidget(move_label, 0, 0, 1, 3);

	mainLayout->addWidget(dx_label, 1, 0);
	mainLayout->addWidget(dx_entry, 1, 1, 1, 2);
	mainLayout->addWidget(dy_label, 2, 0);
	mainLayout->addWidget(dy_entry, 2, 1, 1, 2);
	mainLayout->addWidget(dz_label, 3, 0);
	mainLayout->addWidget(dz_entry, 3, 1, 1, 2);

	mainLayout->addWidget(move_btn, 4, 1);

	mainLayout->addWidget(scale_label, 6, 0, 1, 5);

	mainLayout->addWidget(kx_label, 7, 0);
	mainLayout->addWidget(kx_entry, 7, 1, 1, 2);
	mainLayout->addWidget(ky_label, 8, 0);
	mainLayout->addWidget(ky_entry, 8, 1, 1, 2);
	mainLayout->addWidget(kz_label, 9, 0);
	mainLayout->addWidget(kz_entry, 9, 1, 1, 2);

	mainLayout->addWidget(scale_btn, 10, 1);

	mainLayout->addWidget(rotate_label, 11, 0, 1, 4);

	mainLayout->addWidget(yz_angle_label, 12, 0);
	mainLayout->addWidget(yz_angle_entry, 12, 1, 1, 2);
	mainLayout->addWidget(xz_angle_label, 13, 0);
	mainLayout->addWidget(xz_angle_entry, 13, 1, 1, 2);
	mainLayout->addWidget(xy_angle_label, 14, 0);
	mainLayout->addWidget(xy_angle_entry, 14, 1, 1, 2);

	mainLayout->addWidget(rotate_btn, 15, 1);

	mainLayout->addWidget(file_label, 17, 0, 1, 2);
	mainLayout->addWidget(file_entry, 17, 2);

	mainLayout->addWidget(load_from_btn, 18, 1);
	mainLayout->addWidget(load_to_file_btn, 18, 2);
	mainLayout->addWidget(view, 0, 3, 18, 10);
	setLayout(mainLayout);

	setWindowTitle(tr("3D application"));
}

TransformWidget::~TransformWidget()
{
	this->params.action = free_memory;
	if (params.filename)
		free(params.filename);
	delete move_label;

	delete dy_label;
	delete dz_label;
	
	delete scale_label;
	delete kx_label;
	delete ky_label;
	delete kz_label;
	
	delete rotate_label;
	delete yz_angle_label;
	delete xz_angle_label;
	delete xy_angle_label;
	
	delete file_label;
	
	delete view;

	delete dx_entry;
	delete dy_entry;
	delete dz_entry;

	delete kx_entry;
	delete ky_entry;
	delete kz_entry;
	
	delete xy_angle_entry;
	delete xz_angle_entry;
	delete yz_angle_entry;
	
	delete file_entry;
	
	delete move_btn;
	delete scale_btn;
	delete rotate_btn;
	delete load_from_btn;
	delete load_to_file_btn;

	delete mainLayout;

	make_action(this->params);
}

void TransformWidget::moveClicked()
{
    error_code result = no_errors;
	int i = 0;
	bool dx_empty = dx_entry->text().isEmpty();
	bool dy_empty = dy_entry->text().isEmpty();
	bool dz_empty = dz_entry->text().isEmpty();
	if (dx_empty && dy_empty && dz_empty)
	{
		result = error_input;
	}
	if (!dx_empty)
	{
		this->params.changes[i] = dx_entry->text().toDouble();
		i++;
	}
	else
	{
		this->params.changes[i] = 0;
		i++;
	}
	if (!dy_empty)
	{
		this->params.changes[i] = dy_entry->text().toDouble();
		i++;
	}
	else
	{
		this->params.changes[i] = 0;
		i++;
	}
	if (!dz_empty)
	{
		this->params.changes[i] = dz_entry->text().toDouble();
		i++;
	}
	else
	{
		this->params.changes[i] = 0;
		i++;
	}
	if (!result)
	{
		this->params.action = move_action;
		result = make_action(this->params);
	}
	if (!result)
	{

		view->change_pic();
	}
	else
		error_hadling(result);
}

void TransformWidget::scaleClicked()
{
	error_code result = no_errors;
	int i = 0;
	bool kx_empty = kx_entry->text().isEmpty();
	bool ky_empty = ky_entry->text().isEmpty();
	bool kz_empty = kz_entry->text().isEmpty();
	if (kx_empty && ky_empty && kz_empty)
		result = error_input;
	if (!kx_empty)
	{
		this->params.changes[i] = kx_entry->text().toDouble();
		i++;
	}
	else
	{
		this->params.changes[i] = 1;
		i++;
	}
	if (!ky_empty)
	{
		this->params.changes[i] = ky_entry->text().toDouble();
		i++;
	}
	else
	{
		this->params.changes[i] = 1;
		i++;
	}
	if (!kz_empty)
	{
		this->params.changes[i] = kz_entry->text().toDouble();
		i++;
	}
	else
	{
		this->params.changes[i] = 1;
		i++;
	}
	if (!result)
	{
		this->params.action = scale_action;
		result = make_action(this->params);
	}
	if (!result)
	{
		view->params = params;
		view->change_pic();
	}
	else
		error_hadling(result);
}

void TransformWidget::loadToClicked()
{
	error_code result = no_errors;
	this->params.action = save_model;
	if (file_entry->text().isEmpty())
		result = error_input_filename;
	else
	{
		if (this->params.filename)
			free(this->params.filename);
		QString filename = file_entry->text();
		this->params.filename = (char *) malloc((filename.length() + 1) * sizeof(char));
		if (!this->params.filename)
			result = error_memory;
		else
		{
			memcpy(this->params.filename, filename.toLatin1(), filename.length());
			params.filename[filename.length()] = '\0';
			result = make_action(this->params);
		}
	}
	if (result)
		error_hadling(result);
}

void TransformWidget::rotateClicked()
{
	error_code result = no_errors;
	int i = 0;
	bool yz_empty = yz_angle_entry->text().isEmpty();
	bool xz_empty = xz_angle_entry->text().isEmpty();
	bool xy_empty = xy_angle_entry->text().isEmpty();
	
	if (xy_empty && yz_empty && xz_empty)
		result = error_input;
	if (!yz_empty)
	{
		this->params.changes[i] = yz_angle_entry->text().toDouble() * M_PI / 180;
		i++;
	}
	else
	{
		this->params.changes[i] = 0;
		i++;
	}
	if (!xz_empty)
	{
		this->params.changes[i] = xz_angle_entry->text().toDouble() * M_PI / 180;
		i++;
	}
	else
	{
		this->params.changes[i] = 0;
		i++;
	}
	if (!xy_empty)
	{
		this->params.changes[i] = xy_angle_entry->text().toDouble() * M_PI / 180;
		i++;
	}
	else
	{
		this->params.changes[i] = 0;
		i++;
	}
	if (!result)
	{
		this->params.action = rotate_action;
		result = make_action(this->params);
	}

	if (!result)
	{
		view->params = params;
		view->change_pic();
	}
	else
		error_hadling(result);
}

void TransformWidget::loadFromClicked()
{
	error_code result = no_errors;
	this->params.action = get_model;
	if (file_entry->text().isEmpty())
		result = error_input_filename;
	else
	{
		if (this->params.filename)
			free(this->params.filename);
		QString filename = file_entry->text();
		this->params.filename = (char *) malloc((filename.length() + 1) * sizeof(char));
		if (!this->params.filename)
			result = error_memory;
		else
		{
			memcpy(this->params.filename, filename.toLatin1(), filename.length());
			params.filename[filename.length()] = '\0';
		}
	}
	
	result = make_action(this->params);
	
	if (!result)
	{
		view->params = params;
		view->change_pic();
	}
	else
		error_hadling(result);
}

void TransformWidget::error_hadling(error_code &result)
{
	QMessageBox box;
	switch (result)
	{
		case error_file:
			box.critical(this, "Ошибка", "Не существует файла с таким именем");
			break;
		case error_file_input:
			box.critical(this, "Ошибка", "Некорректный формат (содержимое) файла с параметрами объекта");
			break;
		case error_memory:
			box.critical(this, "Ошибка", "Произошла ошибка при выделении памяти под математическую модель объекта");
			break;
		case error_void:
			box.critical(this, "Ошибка", "Сначала необходимо загрузить модель объекта");
			break;
		case error_input:
			box.critical(this, "Ошибка", "Для изменения объекта необходимо ввести хотя бы один параметр");
			break;
		default:
			break;
	}
}