#ifndef QRIBBONTEST_H
#define QRIBBONTEST_H

#include <QMainWindow>

class QVBoxLayout;
class QRibbonMainwindow : public QMainWindow
{
    Q_OBJECT

public slots:
    void action();
    void indexChanged(int tab);

public:
	QRibbonMainwindow();
    ~QRibbonMainwindow();

	void addOSGViewerWidget(QWidget* wgt);

private:
	void CreateRibbonMenu();

private:
	QVBoxLayout* m_layout;
};

#endif // QRIBBONTEST_H
