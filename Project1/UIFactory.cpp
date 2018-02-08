#include "UIFactory.h"
#include "defaultButton.h"

using namespace std;
using namespace sf;

unique_ptr<Button> UIFactory::createButton(const Texture & up, const Texture & over, const Texture & down, FloatRect hitArea, string caption)
{
	return unique_ptr<Button>(new DefaultButton());
}