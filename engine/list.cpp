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

ENG_API List::~List() {
	this->resetListAndFreeMemory();
}

void ENG_API List::pass(const Node* rootNode) {
	if (rootNode == nullptr || rootNode->getNumberOfChildren() == 0) return;
	for (auto* node : rootNode->getChildren()) {
		this->addRowToListOfNodeToRender(node, node->getFinalMatrix());
		this->pass(node);
	}
}

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

void ENG_API List::clearList() {
	this->resetListAndFreeMemory();
}

void ENG_API List::renderElements(const glm::mat4& cameraInverseFinalMatrix) const {
	for (const auto* reservedRow : this->listOfReservedToRender)
		reservedRow->r_node->render(cameraInverseFinalMatrix * reservedRow->r_nodeFinalMatrix);
}

void ENG_API List::resetListAndFreeMemory() {
	for (auto* element : this->listOfReservedToRender)
		delete element;
	this->listOfReservedToRender.clear();
}