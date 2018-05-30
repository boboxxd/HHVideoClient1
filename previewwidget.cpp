#include "previewwidget.h"
#include <QGridLayout>
PreviewWidget::PreviewWidget(QWidget *parent) : QWidget(parent)
{

}

void PreviewWidget::resizeEvent(QResizeEvent *event)
{
    pix= QPixmap(pixname).scaled(label.size(),Qt::KeepAspectRatio);
    label.setPixmap(pix);
}

void PreviewWidget::getimagename(const QString &name)
{
    pixname =name;
}
