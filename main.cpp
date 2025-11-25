#include <iostream>
#include <SFML/Graphics.hpp>
#include <unordered_map>
#include <vector>
#include <cstdlib>
using namespace std;
class windowparams;
struct hanoiDimensions;
sf::Vector2f blockposition( int blocknum, int column, windowparams &param1 );
struct hanoiDimensions{
    int blockWidth;
    int blockHeight;
};
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

class hanoiTowers{
    sf::RectangleShape tower;
    vector<int> blockTrack;
    public:
    sf::RectangleShape& getTower(){
        return tower;
    }
    vector<int>& getTrack(){
        return blockTrack;
    }
};

//sf::Vector2f blockposition( int blocknum, int column, windowparams &param1 );
class hanoiblock{
        int blocknum;
        int column;
        sf::RectangleShape block;
        windowparams &param1;
    public:
        hanoiblock( const hanoiblock& block1 ) : blocknum(block1.blocknum), column( block1.column ), block( block1.block ), param1( block1.param1 ){
            //blocknum = block1.blocknum;
            //column = block1.column;
            //block = block1.block;
            //param1 = block1.param1;
            block.setPosition( block1.block.getPosition() );
            block.setSize( block1.block.getSize() );

        }
        hanoiblock( int blocknum1, int totBlocks, windowparams &param11, int column1 = 0, sf::Vector2i position1 = { 0, 0 } ) : blocknum(blocknum1), column(column1), param1(param11){
            block.setPosition( blockposition( ( totBlocks - blocknum ), column, param11 ) );
            block.setSize({ param11.blockdimensions.blockWidth, param11.blockdimensions.blockHeight });
        }
        void setPosition( int blocknum, int column, windowparams &param1 ){
            block.setPosition( blockposition( blocknum, column, param1 ) );
            this->column = column;
        }
        sf::RectangleShape& getBlock(){
            return block;
        }

};

int main(){
    //int windowWidth, windowHeight;
    int totBlocks;
    windowparams param1;
    param1.windowWidth = 800;
    param1.windowHeight = 600;
    param1.hanoiDistance = param1.windowWidth / 4;
    param1.towerLength = static_cast<int>( param1.windowHeight / 1.9 );
    sf::RenderWindow window1( sf::VideoMode({ param1.windowWidth, param1.windowHeight }), "Hanoi" );
    sf::View view1;
    view1.setSize( { param1.windowWidth, param1.windowHeight } );
    view1.setCenter( { param1.windowWidth / 2, param1.windowHeight / 2 } );
    window1.setFramerateLimit(1);
    window1.setView( view1 );
    srand(time(0));
    vector<hanoiTowers> towers;
    vector<hanoiblock> blocks;
    towers.resize(3);
    cout<<"Enter the number of hanoi blocks";
    cin>>totBlocks;
    param1.computeDimensions( window1, totBlocks );
    for( int i = 0; i < totBlocks; i++ ){
        int random1 = rand() % 256;
        int random2 = rand() % 256;
        int random3 = rand() % 256;
        //int random1[3];
        //for( int random : random1 ){
        //    random = rand() % 255;
        //}
        towers[0].getTrack().push_back(i);
        blocks.push_back(hanoiblock(i, totBlocks, param1));
        blocks[i].getBlock().setFillColor( sf::Color( random1, random2, random3 ) );
        window1.draw(blocks[i].getBlock());
    }
    //window1.draw(blocks[1].getBlock());
    while(window1.isOpen()){
        while( const std::optional event = window1.pollEvent() ){
            if( event -> is<sf::Event::Closed>() ){
                window1.close();
            }
        }
        window1.display();
    }
    
}
sf::Vector2f blockposition( int blocknum, int column, windowparams &param1 ){
    sf::Vector2f temp( static_cast<float>(column * param1.hanoiDistance), static_cast<float>( param1.towerBase - ( blocknum - 1 ) * param1.blockdimensions.blockHeight ) );
    return temp;

}