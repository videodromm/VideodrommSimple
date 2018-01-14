
#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"
#include "cinder/GeomIo.h"
#include "cinder/CameraUi.h"
#include "cinder/Camera.h"
#include "cinder/Log.h"
#include "cinder/Utilities.h"
#include "cinder/params/Params.h"
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
private:
	gl::QueryTimeSwappedRef mGpuTimer;
	Timer					mCpuTimer;
	float					mAverageGpuTime = 0.0f;
	float					mAverageCpuTime = 0.0f;
	params::InterfaceGlRef	mParams;
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
	mGpuTimer = gl::QueryTimeSwapped::create();
	gl::enableVerticalSync();

	auto geometry = geom::RoundedRect() >> geom::Scale(vec3(10));
	mBatch = gl::Batch::create(geometry, gl::getStockShader(gl::ShaderDef().lambert()));

	gl::enableDepth();
	mParams = params::InterfaceGl::create("Options", ivec2(260, 50));
	mParams->addParam("Average GPU Draw (ms)", &mAverageGpuTime);
	mParams->addParam("Average CPU Draw (ms)", &mAverageCpuTime);
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
	getWindow()->setTitle("(" + toString( (int)getAverageFps() ) + " fps) Videodromm");
}

void VideodrommSimpleApp::draw()
{
	mGpuTimer->begin();
	mCpuTimer.start();
	gl::clear(Color(0, 0, 0));
	gl::setMatrices(mCamera);
	mBatch->draw();
	mCpuTimer.stop();
	mGpuTimer->end();

	mAverageCpuTime = (mCpuTimer.getSeconds() * 200) + mAverageCpuTime * 0.8f;
	mAverageGpuTime = mGpuTimer->getElapsedMilliseconds() * 0.2f + mAverageGpuTime * 0.8f;

	mSpoutOut.sendViewport();
	mParams->draw();
}

void VideodrommSimpleApp::resize()
{
	mCamera.setAspectRatio(app::getWindowAspectRatio());
	
}

CINDER_APP(VideodrommSimpleApp, RendererGl{ RendererGl::Options().msaa(16) }, &VideodrommSimpleApp::prepare)

