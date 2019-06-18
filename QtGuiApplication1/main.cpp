
#include <QtWidgets/QApplication>

#include <QApplication>
#include <osgViewer/Viewer>
#include <osgGA/TrackballManipulator>
#include <osgQt/GraphicsWindowQt>
#include <osg/MatrixTransform>
#include <osgManipulator/TabBoxDragger>
#include <osgGA/StateSetManipulator>
#include <osgViewer/ViewerEventHandlers>
#include <osgDB/ReadFile>
#include <osgEarth/Map>
#include <osgEarth/MapNode>
#include <osgEarthDrivers/gdal/GDALOptions>
#include <osgEarthDrivers/tms/TMSOptions>
#include <osgEarth/ImageLayer>
#include<osgEarthDrivers/gdal/GDALOptions>

#include<osgEarthDrivers/bing/BingOptions>
#include <QMdiArea>
#include <QGridLayout>
#include "QTextCodec"

#include "qribbonMainwindow.h"

int main(int argc, char** argv)
{
	QApplication app(argc, argv);
	
	//! 中文支持
	QTextCodec::setCodecForLocale(QTextCodec::codecForName("GB2312"));

	QRibbonMainwindow mainWin;
	mainWin.show();

	QWidget *md = new QWidget(&mainWin);
	md->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	//md->showMaximized();
	md->setMinimumSize(800, 600);

	QGridLayout *grid = new QGridLayout;
	md->setLayout(grid);
	//osgQt::initQtWindowingSystem();
	
	osg::ref_ptr<osgEarth::Map> map = new osgEarth::Map;
	osgViewer::ViewerBase::ThreadingModel threadingModel = osgViewer::ViewerBase::SingleThreaded;
	osg::ref_ptr<osgEarth::MapNode> mapNode = new osgEarth::MapNode(map);
	osg::ref_ptr<osgViewer::Viewer> viewer = new osgViewer::Viewer;

	osgEarth::Drivers::BingOptions bing;
	osgEarth::Drivers::GDALOptions gdal;
	osgEarth::Drivers::TMSOptions tms;
	tms.url() = "D:/data/world/tms.xml";
	gdal.url() = "H:\\osgearthSDK\\Data\\world.tif";
	map->addLayer(new osgEarth::ImageLayer("My", gdal));
	viewer->addEventHandler(new osgViewer::StatsHandler);
	viewer->addEventHandler(new osgGA::StateSetManipulator());
	viewer->setCameraManipulator(new osgGA::TrackballManipulator);
	viewer->setSceneData(mapNode);
	viewer->setThreadingModel(threadingModel);
	//viewer->realize();
	osgQt::setViewer(viewer.get());
	osgQt::GLWidget* glw = new osgQt::GLWidget(md);
	osgQt::GraphicsWindowQt* graphicswin = new osgQt::GraphicsWindowQt(glw);
	viewer->getCamera()->setViewport(new osg::Viewport(0, 0, glw->width(), glw->height()));
	viewer->getCamera()->setGraphicsContext(graphicswin);

	grid->addWidget(glw);

	mainWin.addOSGViewerWidget(md);
	return app.exec();
}
