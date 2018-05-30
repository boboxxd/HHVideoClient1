#ifndef PREVIEWWIDGET_H
#define PREVIEWWIDGET_H

#include <QWidget>
#include <QLabel>
class PreviewWidget : public QWidget
{
    Q_OBJECT
public:
    explicit PreviewWidget(QWidget *parent = nullptr);
    void resizeEvent(QResizeEvent *event);

signals:

public slots:
    void getimagename(const QString& name);
private:
    QLabel label;
    QPixmap pix;
    QString pixname;
};

#endif // PREVIEWWIDGET_H
