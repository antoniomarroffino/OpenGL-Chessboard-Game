#include "list.h"
#include "light.h"
#include "camera.h"

struct ENG_API List::Reserved {
	Object* r_node;
	glm::mat4 r_nodeFinalMatrix;

	Reserved(Object* node, const glm::mat4& finalMatrix) : r_node{node}, r_nodeFinalMatrix{finalMatrix} 
	{}
};

ENG_API List::List() : reserved{std::unique_ptr<List::Reserved>()}, listOfReservedToRender{std::list<List::Reserved*>()} {}

ENG_API bool List::addRowToListOfNodeToRender(Object* node, const glm::mat4& finalMatrix) {
	if (node == nullptr || dynamic_cast<Camera*>(node) != nullptr) return false;

	List::Reserved* reservedRow = new List::Reserved(node, finalMatrix);
	Light* optionalLight = dynamic_cast<Light*>(node);
	if (optionalLight != nullptr)
		this->listOfReservedToRender.push_front(reservedRow);
	else
		this->listOfReservedToRender.push_back(reservedRow);
	return true;
}

ENG_API void List::clearList() {
	for (auto* el : this->listOfReservedToRender)
		delete el;
	this->listOfReservedToRender.clear();
}

ENG_API void List::renderElements(const glm::mat4& cameraFinalMatrix) const {
	for (const auto* reservedRow : this->listOfReservedToRender)
		reservedRow->r_node->render(cameraFinalMatrix * reservedRow->r_nodeFinalMatrix);
}