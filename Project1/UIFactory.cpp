#include "UIFactory.h"
#include "defaultButton.h"

using namespace std;
using namespace sf;

unique_ptr<Button> UIFactory::createButton(const Texture & up, const Texture & over, const Texture & down, FloatRect hitArea, string caption, Vector2f location)
{
	return unique_ptr<Button>(new DefaultButton(up, over, down, hitArea, caption, location));
}