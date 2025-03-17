#include "inputfieldsize.h"

InputFieldSize::InputFieldSize(const QString &label1Text, const QString &label2Text, QWidget *parent)
    : QDialog(parent) {

    label1 = new QLabel(label1Text);
    label2 = new QLabel(label2Text);
    lineEdit1 = new QLineEdit;
    lineEdit2 = new QLineEdit;
    okButton = new QPushButton("OK");
    cancelButton = new QPushButton("Cancel");

    // Layout
    QVBoxLayout *mainLayout = new QVBoxLayout;

    QHBoxLayout *layout1 = new QHBoxLayout;
    layout1->addWidget(label1);
    layout1->addWidget(lineEdit1);
    mainLayout->addLayout(layout1);

    QHBoxLayout *layout2 = new QHBoxLayout;
    layout2->addWidget(label2);
    layout2->addWidget(lineEdit2);
    mainLayout->addLayout(layout2);

    QHBoxLayout *buttonLayout = new QHBoxLayout;
    buttonLayout->addWidget(okButton);
    buttonLayout->addWidget(cancelButton);
    mainLayout->addLayout(buttonLayout);

    setLayout(mainLayout);

    // Connections
    connect(okButton, &QPushButton::clicked, this, &QDialog::accept);
    connect(cancelButton, &QPushButton::clicked, this, &QDialog::reject);

    setWindowTitle("Input Dialog");
}

QString InputFieldSize::getText1() const {
    return lineEdit1->text();
}

QString InputFieldSize::getText2() const {
    return lineEdit2->text();
}
