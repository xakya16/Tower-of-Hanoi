#include <iostream>
#include <SFML/Graphics.hpp>
using namespace std;
class windowparams{
    public:
    int windowWidth, windowHeight;
    int hanoiDistance;
    int towerLength;
    int towerBase;
    hanoiDimensions blockdimensions;
    void computeDimensions( sf::RenderWindow &window1, int totBlocks ){
        windowWidth = window1.getSize().x;
        windowHeight = window1.getSize().y;
        towerLength = static_cast<int>( windowHeight / 1.9 );
        towerBase = 0.8 * windowHeight;
        blockdimensions.blockWidth = hanoiDistance * 0.6;
        blockdimensions.blockHeight = towerLength / totBlocks;
    };
};
struct hanoiDimensions{
    int blockWidth;
    int blockHeight;
};

sf::Vector2f blockposition( int blocknum, int column, windowparams &param1 );
class hanoiblock{
        int blocknum;
        int column;
        sf::RectangleShape block;
        windowparams &param1;
    public:
        hanoiblock( int blocknum1, int totBlocks, windowparams &param11, int column1 = 0, sf::Vector2i position1 = { 0, 0 } ) : blocknum(blocknum1), column(column1), param1(param11){
            block.setPosition( blockposition( ( totBlocks - blocknum ), column, param11 ) );
        }
        void setPosition( int blocknum, int column, windowparams &param1 ){
            block.setPosition( blockposition( blocknum, column, param1 ) );
        }

};
int main(){
    //int windowWidth, windowHeight;
    windowparams param1;
    param1.windowWidth = 800;
    param1.windowHeight = 600;
    param1.hanoiDistance = param1.windowWidth / 4;
    param1.towerLength = static_cast<int>( param1.windowHeight / 1.9 );
    sf::RenderWindow window1( sf::VideoMode({ param1.windowWidth, param1.windowHeight }), "Hanoi" );
    sf::View view1;
    view1.setSize( { param1.windowWidth, param1.windowHeight } );
    view1.setCenter( { param1.windowWidth / 2, param1.windowHeight / 2 } );
    window1.setView( view1 );
    
}
sf::Vector2f blockposition( int blocknum, int column, windowparams &param1 ){
    return { column * param1.hanoiDistance, ( param1.towerBase - ( blocknum - 1 ) * param1.blockdimensions.blockHeight ) };
}