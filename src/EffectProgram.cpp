#include "EffectProgram.h"

using namespace ci;

EffectProgram::EffectProgram(ci::gl::BatchRef prog) :
	Program(prog), mLastUpdatedFrame(0)
{
	updateUniform("tex_base", 0);
}

EffectProgramRef EffectProgram::create(std::string frag) {
	gl::GlslProgRef prog = gl::GlslProg::create(app::loadAsset("shaders/passthrough.vert"), app::loadAsset(frag));
	gl::BatchRef batch = gl::Batch::create(geom::Rect(app::getWindowBounds()), prog);
	prog->uniform("i_resolution", (vec2) app::getWindowSize());
	return EffectProgramRef(new EffectProgram(batch));
}

std::shared_ptr<ci::Camera> EffectProgram::camera()
{
	return nullptr;
}

std::shared_ptr<ci::ivec2> EffectProgram::matrixWindow()
{
	return std::make_shared<ivec2>(app::getWindowSize());
}

ci::gl::Texture2dRef EffectProgram::getColorTexture(ci::gl::FboRef a, ci::gl::FboRef b)
{
	gl::ScopedTextureBind tex(mBaseProg->getColorTexture(b, a), 0);

	gl::ScopedFramebuffer sfbo(a);
	gl::ScopedViewport svp(a->getSize());
	gl::ScopedMatrices mats();
	gl::setMatricesWindow(a->getSize());

	Program::draw();

	return a->getColorTexture();
}

void EffectProgram::draw(ci::gl::FboRef a, ci::gl::FboRef b) {
	gl::ScopedTextureBind tex(mBaseProg->getColorTexture(b, a), 0);

	Program::draw();
}

void EffectProgram::setBase(ProgramRef p)
{
	mBaseProg = p;
}