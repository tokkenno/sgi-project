#include "scene_object.h"

namespace Engine {
	namespace Core {
		Utils::Logger* SceneObject::logger = Utils::Logger::getLogger("Engine::Core::SceneObject");

		SceneObject::SceneObject() : position(0, 0, 0), rotation(0, 0, 0)
		{
		}


		SceneObject::~SceneObject()
		{
		}

		void SceneObject::internalDraw() {
			this->draw();

			for (std::list<SceneObject*>::iterator it = this->childs.begin(); it != this->childs.end(); ++it) {
				(*it)->internalDraw();
			}
		}

		void SceneObject::draw() {
			logger->error(__FUNCTION__, "Todas las clases heredadas de SceneObject deben sobreescribir el metodo draw().");
		}

		void SceneObject::setParent(SceneObject* parentPtr) {
			this->parent = parentPtr;
		}

		void SceneObject::rotate(float_t x, float_t y, float_t z) {
			float_t ix = this->rotation.getX() + x;
			float_t iy = this->rotation.getY() + y;
			float_t iz = this->rotation.getZ() + z;

			if (ix > 360) ix -= 360; else if (ix < 0) ix += 360;
			if (iy > 360) iy -= 360; else if (iy < 0) ix += 360;
			if (iz > 360) iz -= 360; else if (iz < 0) ix += 360;

			this->rotation.setX(ix);
			this->rotation.setY(iy);
			this->rotation.setZ(iz);
		}

		void SceneObject::translate(float_t x, float_t y, float_t z) {
			this->position.setX(this->position.getX() + x);
			this->position.setY(this->position.getY() + y);
			this->position.setZ(this->position.getZ() + z);
		}

		void SceneObject::addChild(SceneObject* child) {
			if (!(std::find(this->childs.begin(), this->childs.end(), child) != this->childs.end())) {
				this->childs.push_back(child);
				child->setParent(this);
			}
		}

		void SceneObject::removeChild(SceneObject* child) {
			if ((std::find(this->childs.begin(), this->childs.end(), child) != this->childs.end())) {
				this->childs.remove(child);
				child->setParent(NULL);
			}
		}

		SceneObject* SceneObject::getParent() const {
			return this->parent;
		}
	}
}