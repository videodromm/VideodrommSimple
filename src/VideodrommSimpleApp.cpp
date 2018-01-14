
#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"
#include "cinder/GeomIo.h"
#include "cinder/CameraUi.h"
#include "cinder/Camera.h"

#include "CiSpoutOut.h"

using namespace ci;
using namespace ci::app;
using namespace std;

class VideodrommSimpleApp : public App {
public:
	static void prepare(Settings *settings);
	VideodrommSimpleApp();
	void mouseDrag(MouseEvent event) override;
	void mouseDown(MouseEvent event) override;
	void mouseUp(MouseEvent event) override;
	void update() override;
	void draw() override;
	void resize() override;

	gl::BatchRef mBatch;

	CameraPersp		mCamera;
	CameraUi		mCameraUi;

	SpoutOut mSpoutOut;
};
void VideodrommSimpleApp::prepare(Settings *settings)
{
	settings->setWindowSize(640, 480);
	// settings->setBorderless();
}
VideodrommSimpleApp::VideodrommSimpleApp()
	: mCameraUi(&mCamera)
	, mSpoutOut("videodromm simple", app::getWindowSize())
{
	auto geometry = geom::Teapot() >> geom::Scale(vec3(10));
	mBatch = gl::Batch::create(geometry, gl::getStockShader(gl::ShaderDef().lambert()));

	gl::enableDepth();
}

void VideodrommSimpleApp::mouseDrag(MouseEvent event)
{
	mCameraUi.mouseDrag(event);
}

void VideodrommSimpleApp::mouseDown(MouseEvent event)
{
	mCameraUi.mouseDown(event);
}

void VideodrommSimpleApp::mouseUp(MouseEvent event)
{
	mCameraUi.mouseUp(event);
}

void VideodrommSimpleApp::update()
{
}

void VideodrommSimpleApp::draw()
{
	gl::clear(Color(0, 0, 0));
	gl::setMatrices(mCamera);
	mBatch->draw();

	mSpoutOut.sendViewport();
}

void VideodrommSimpleApp::resize()
{
	mCamera.setAspectRatio(app::getWindowAspectRatio());
	
}

CINDER_APP(VideodrommSimpleApp, RendererGl{ RendererGl::Options().msaa(16) }, &VideodrommSimpleApp::prepare)

