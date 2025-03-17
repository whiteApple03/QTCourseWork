#ifndef INPUTFIELDSIZE_H
#define INPUTFIELDSIZE_H

#include <QDialog>
#include <QLineEdit>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
class InputFieldSize : public QDialog
{
    Q_OBJECT

public:
    InputFieldSize(const QString &label1, const QString &label2, QWidget *parent = nullptr);
    QString getText1() const;
    QString getText2() const;

private:
    QLabel *label1;
    QLabel *label2;
    QLineEdit *lineEdit1;
    QLineEdit *lineEdit2;
    QPushButton *okButton;
    QPushButton *cancelButton;
};

#endif // INPUTFIELDSIZE_H
