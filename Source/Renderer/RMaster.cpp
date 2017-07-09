#include "RMaster.h"

#include "../Display.h"
#include "../World/Block/BlockDatabase.h"

#include "../Maths/Matrix.h"

#include "../Camera.h"

namespace Renderer
{
    void Master::clear()
    {
        Display::get().clear();
    }

    void Master::update(const Camera& camera)
    {
        ///@TODO This is starting to feel a bit bad
        ///Another way to do this?
        Block::Database::get().getTextureAtlas().bind();

        glEnable(GL_DEPTH_TEST);
        m_simpleRenderer.update(camera);

        glDisable(GL_DEPTH_TEST);
        m_sfmlRenderer.update ();

        Display::get().update();
    }

    void Master::draw(const sf::Drawable& drawable)
    {
        m_sfmlRenderer.draw(drawable);
    }

    void Master::draw(const Cube& cube)
    {
        m_simpleRenderer.draw(cube);
    }
}
