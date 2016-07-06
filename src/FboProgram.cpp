#include "FboProgram.h"

using namespace ci;

BaseProgramRef FboProgram::create(ProgramRef b)
{
	ci::gl::FboRef fbo = gl::Fbo::create(app::getWindowWidth(), app::getWindowHeight());
	return BaseProgramRef(new FboProgram(b, fbo));
}

std::shared_ptr<ci::Camera> FboProgram::camera()
{
	return mProg->camera();
}

std::shared_ptr<ci::ivec2> FboProgram::matrixWindow()
{
	return mProg->matrixWindow();
}

ci::gl::TextureRef FboProgram::getColorTexture()
{
	update();

	return mFbo->getColorTexture();
}

FboProgram::FboProgram(ProgramRef p, ci::gl::FboRef f) : BaseProgram(p), mProg(p), mFbo(f), mLastUpdatedFrame(0)
{
}

void FboProgram::update()
{
	if (mLastUpdatedFrame >= app::getElapsedFrames()) {
		return;
	}

	mLastUpdatedFrame = app::getElapsedFrames();

	gl::ScopedFramebuffer fbo(mFbo);
	mProg->draw();
}