#include "Camera.h"

// getters
View Camera::getView() const
{
    return this->view;
}

// setters
void Camera::setMapSize(Vector2f mapSize)
{
    this->mapSize = mapSize;
}

// zoom in-out
void Camera::zoomEvent(int value)
{
    // to add code using view.zoom() function
}

void Camera::handleView(Character character)
{
    Vector2f playerPosition = character.getCharacterPosition();

    // to position camera on the map, not outside it, if camera is centred on character while he's being on map corners
    Vector2f sizeCamera = this->view.getSize();
    float cameraXleft = playerPosition.x - sizeCamera.x / 2;
    float cameraXright = playerPosition.x + sizeCamera.x / 2;
    float cameraYup = playerPosition.y - sizeCamera.y / 2;
    float cameraYdown = playerPosition.y + sizeCamera.y / 2;

    this->view.setCenter(Vector2f(playerPosition.x,playerPosition.y));

    if(cameraXleft < 0 || cameraYup < 0 || cameraXright > this->mapSize.x || cameraYdown > this->mapSize.y)
        {
            float moveX = 0, moveY=0;

            if(cameraXleft<0)
                moveX = -cameraXleft;
            if(cameraXright > this->mapSize.x)
                moveX = -(cameraXright - this->mapSize.x);

            if(cameraYup<0)
                moveY = -cameraYup;
            if(cameraYdown > this->mapSize.y)
                moveY = -(cameraYdown - this->mapSize.y);

            this->view.move(moveX,moveY);
        }
    else
        {
            this->view.setCenter(Vector2f(playerPosition.x,playerPosition.y));
        }
}

// constructors
Camera::Camera()
{
    string pathValues = "values/options/options.json";
    ifstream file(pathValues);
    nlohmann::json data = nlohmann::json::parse(file);

    this->windowSize.x = (data["windowSizeX"].is_null()?0:(float)data["windowSizeX"]);
    this->windowSize.y = (data["windowSizeY"].is_null()?0:(float)data["windowSizeY"]);

    this->view.setSize(Vector2f(this->windowSize.x,this->windowSize.y));
}

// destructors
Camera::~Camera()
{

}
