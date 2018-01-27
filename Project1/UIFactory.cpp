#include "UIFactory.h"
#include "button.h"

using namespace std;
using namespace sf;

unique_ptr<ButtonInterface> UIFactory::createButton(const Texture & up, const Texture & over, const Texture & down, FloatRect hitArea, string caption, Vector2f location)
{
	return unique_ptr<ButtonInterface>(new Button(up, over, down, hitArea, caption, location));
}