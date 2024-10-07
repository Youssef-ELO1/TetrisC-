// dimensiondialog.h
#ifndef DIMENSIONDIALOG_H
#define DIMENSIONDIALOG_H

#include <QDialog>
#include <QLineEdit>

class DimensionDialog : public QDialog
{
    Q_OBJECT

public:
    DimensionDialog(QWidget *parent = nullptr);
    ~DimensionDialog();
    void checkValuesAndAccept();
    void closeParent();
    void defaultValues();

    int getCols() const;
    int getRows() const;

private:
    QLineEdit *colsLineEdit;
    QLineEdit *rowsLineEdit;
};

#endif // DIMENSIONDIALOG_H
