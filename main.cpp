#include <iostream>
#include <SFML/Graphics.hpp>
#include <ctime>
#include <unordered_map>
#include <vector>
#include <cstdlib>
using namespace std;
class windowparams;
struct hanoiDimensions;
class hanoiTowers;
class hanoiblock;
sf::Vector2f getcenterpoint( sf::RectangleShape &shape1 );
sf::Vector2f blockposition( int blocknum, int column, windowparams &param1, int , int position1 );
float blockwidthcomputation( int blocknum1, windowparams &param1, int totBlocks );
hanoiblock* checkhanoihover( std::vector<hanoiTowers>& towers, sf::RenderWindow &window1 );
bool checkhover( sf::RectangleShape block, sf::Vector2f point );
//bool checkhanoihover(std::vector<hanoiTowers>);
struct hanoiDimensions{
    int minBlockWidth;
    int maxBlockWidth;
    int blockHeight;
};
struct towerDimensions{
    int towerBase;
    int towerLength;
    int baseWidth;
    int towerWidth;
};
class windowparams{
    public:
    int windowWidth, windowHeight;
    int hanoiDistance;
    towerDimensions towDimensions;
    //int towerLength;
    //int towerBase;
    //int baseWidth;
    hanoiDimensions blockdimensions;
    void computeDimensions( sf::RenderWindow &window1, int totBlocks ){
        windowWidth = window1.getSize().x;
        windowHeight = window1.getSize().y;
        towDimensions.towerLength = static_cast<int>( windowHeight / 1.9 );
        towDimensions.towerBase = 0.8 * windowHeight;
        blockdimensions.maxBlockWidth = hanoiDistance * 0.6;
        blockdimensions.minBlockWidth = 30;
        blockdimensions.blockHeight = 20;
    };
};

class hanoiTowers{
    sf::RectangleShape tower;
    sf::RectangleShape base;
    sf::RectangleShape towersprite;
    vector<int> blockTrack;
    vector<hanoiblock> blocks;
    public:
    hanoiTowers( int towerNum, windowparams& param11 ){
        base.setSize( { param11.hanoiDistance * 0.9, param11.towDimensions.baseWidth } );
        base.setPosition( { param11.hanoiDistance * towerNum - base.getSize().x / 2, param11.towDimensions.towerBase } );
        tower.setSize( { param11.towDimensions.towerWidth, param11.towDimensions.towerLength } );
        tower.setPosition( { param11.hanoiDistance * towerNum - ( param11.towDimensions.towerWidth / 2 ), ( param11.towDimensions.towerBase - param11.towDimensions.towerLength ) } );
        towersprite.setSize( { param11.hanoiDistance * 0.9, param11.towDimensions.towerLength } );
        towersprite.setPosition( { param11.hanoiDistance * towerNum - towersprite.getSize().x / 2, ( param11.towDimensions.towerBase - towersprite.getSize().y ) } );
        towersprite.setFillColor( sf::Color( 0, 0, 0, 0 ) );
        tower.setFillColor( sf::Color( 150, 75, 0 ) );
        base.setFillColor( sf::Color( 150, 75, 0 ) );
    }
    hanoiTowers( const hanoiTowers& tower1 ){
        base.setSize( tower1.base.getSize() );
        base.setPosition( tower1.base.getPosition() );
        base.setFillColor( tower1.base.getFillColor() );
        tower.setSize( tower1.tower.getSize() );
        tower.setPosition( tower1.tower.getPosition() );
        tower.setFillColor( tower1.tower.getFillColor() );
        towersprite.setSize( tower1.towersprite.getSize() );
        towersprite.setPosition( tower1.towersprite.getPosition() );
        towersprite.setOutlineColor( tower1.towersprite.getOutlineColor() );
    }
    sf::RectangleShape& getTower(){
        return tower;
    }
    sf::RectangleShape& getBase(){
        return base;
    }
    sf::RectangleShape& getTowerSprite(){
        return towersprite;
    }
    vector<int>& getTrack(){
        return blockTrack;
    }
    vector<hanoiblock>& getBlocks(){
        return blocks;
    }
    hanoiblock& getHanoiBlock( int blocknum ){
        return blocks[blocknum];
    }
};

//sf::Vector2f blockposition( int blocknum, int column, windowparams &param1 );
class hanoiblock{
        int blocknum;
        int column;
        sf::RectangleShape block;
        //windowparams &param1;
    public:
        hanoiblock( const hanoiblock& block1 ) : blocknum(block1.blocknum), column( block1.column ), block( block1.block )/*, param1( block1.param1 )*/{
            //blocknum = block1.blocknum;
            //column = block1.column;
            //block = block1.block;
            //param1 = block1.param1;
            block.setPosition( block1.block.getPosition() );
            block.setSize( block1.block.getSize() );

        }
        hanoiblock( int blocknum1, int totBlocks, windowparams &param11, int column1 = 1, sf::Vector2i position1 = { 0, 0 } ) : blocknum(blocknum1), column(column1)/*, param1(param11)*/{
            block.setPosition( blockposition( blocknum, column, param11, totBlocks, ( totBlocks - blocknum ) ) );
            block.setSize({ blockwidthcomputation( blocknum, param11, totBlocks ), param11.blockdimensions.blockHeight });
        }
        //hanoiblock operator=( hanoiblock& block1 ){
        //    return hanoiblock( block1.blocknum, )
        //}
        void setPosition( int blocknum, int column, windowparams &param1, int totBlocks ){
            block.setPosition( blockposition( blocknum, column, param1, totBlocks, blocknum ) );
            this->column = column;
        }
        sf::RectangleShape& getBlock(){
            return block;
        }
        int getColumn(){
            return column;
        }
        void setColumn( int column1 ){
            column = column1;
        }
        int getBlocknum(){
            return blocknum;
        }
};

int main(){
    //int windowWidth, windowHeight;
    sf::Clock dtclock;
    float dt = 0.f;
    //srand(time(0));
    int totBlocks;
    windowparams param1;
    param1.windowWidth = 800;
    param1.windowHeight = 600;
    param1.hanoiDistance = param1.windowWidth / 4;
    param1.towDimensions.towerLength = static_cast<int>( param1.windowHeight / 1.9 );
    param1.towDimensions.towerWidth = 3;
    param1.towDimensions.baseWidth = 3;
    sf::RenderWindow window1( sf::VideoMode({ param1.windowWidth, param1.windowHeight }), "Hanoi" );
    sf::View view1;
    view1.setSize( { param1.windowWidth, param1.windowHeight } );
    view1.setCenter( { param1.windowWidth / 2, param1.windowHeight / 2 } );
    window1.setFramerateLimit(10);
    window1.setView( view1 );
    srand(time(0));
    sf::Font font1;
    if( font1.openFromFile("C:\\Users\\Hp\\Desktop\\proj\\calibri.ttf") ){}
    sf::Text coordinates(font1);
    coordinates.setPosition({ 5.f, 5.f });
    coordinates.setString("");
    bool buttonpressed = false;
    bool mousehold = false;
    hanoiblock* dragblock = nullptr;
    sf::Vector2f initPosition = { 0.f, 0.f };
    vector<hanoiTowers> towers;
    //vector<hanoiblock> blocks;
    //towers.resize(3);
    cout<<"Enter the number of hanoi blocks";
    cin>>totBlocks;
    param1.computeDimensions( window1, totBlocks );
    for( int i = 0; i < 3; i++ ){
        towers.push_back( hanoiTowers( ( i + 1 ), param1 ) );
        window1.draw( towers[i].getBase() );
        window1.draw( towers[i].getTower() );
        window1.draw( towers[i].getTowerSprite() );
    }
    for( int i = 0; i < totBlocks; i++ ){
        int random1 = rand() % 256;
        int random2 = rand() % 256;
        int random3 = rand() % 256;
        //int random1[3];
        //for( int random : random1 ){
        //    random = rand() % 255;
        //}
        towers[0].getTrack().push_back(i);
        towers[0].getBlocks().push_back(hanoiblock(i, totBlocks, param1));
        cout<<"Test Point";
        towers[0].getHanoiBlock(i).getBlock().setFillColor( sf::Color( random1, random2, random3 ) );
        window1.draw(towers[0].getHanoiBlock(i).getBlock());
    }
    //window1.draw(blocks[1].getBlock());
    while(window1.isOpen()){
        window1.clear();
        window1.setView( view1 );
        for( int i = 0; i < 3; i++ ){
            //window1.draw( towers[i].getTowerSprite() );
            window1.draw( towers[i].getTower() );
            window1.draw( towers[i].getBase() );
            for( auto &block1 : towers[i].getBlocks() ){
                window1.draw( block1.getBlock() );
            }
        }
        window1.display();
        while( const std::optional event = window1.pollEvent() ){
            if( event -> is<sf::Event::Closed>() ){
                window1.close();
            }
            if( event -> is<sf::Event::MouseButtonReleased>() ){
                buttonpressed = false;
                dtclock.reset();
                if( mousehold == true && dragblock != nullptr ){
                    //bool checkhover1 = false;
                    cout<<"\n\nExecuted\n\n";
                    for( int i = 0; i < 3; i++ ){
                        cout<<"Size"<<towers[i].getBlocks().size();
                        cout<<"\n\nSprite"<<towers[i].getTowerSprite().getPosition().x<<"\t"<<towers[i].getTowerSprite().getPosition().y<<endl<<endl;
                        cout<<"Center"<<getcenterpoint( dragblock->getBlock() ).x<<"\t"<<getcenterpoint( dragblock->getBlock() ).y;
                        cout<<"Towerspritecheck"<<( ( towers[i].getBlocks().size() > 0 )? towers[i].getBlocks()[0].getBlocknum() : 10 )<<"Towerspritecheck < "<<dragblock->getBlocknum()<<endl;
                        cout<<dragblock->getColumn()<<endl;
                        cout<<"Spritesize"<<checkhover( towers[i].getTowerSprite(), getcenterpoint( dragblock->getBlock() ) );
                        if( checkhover( towers[i].getTowerSprite(), getcenterpoint( dragblock->getBlock() ) )  && ( i != ( dragblock->getColumn() - 1 ) ) && ( ( ( towers[i].getBlocks().size() > 0 )? towers[i].getBlocks()[0].getBlocknum() : 10000 ) > dragblock->getBlocknum() ) ){
                            towers[i].getBlocks().insert( towers[i].getBlocks().begin(), *dragblock );
                            towers[i].getBlocks()[0].setColumn( i + 1 );
                            towers[i].getTrack().insert( towers[i].getTrack().begin(), dragblock->getBlocknum() );
                            towers[ ( dragblock->getColumn() - 1 ) ].getBlocks().erase( towers[ ( dragblock->getColumn() - 1 ) ].getBlocks().begin() );
                            towers[ ( dragblock->getColumn() - 1) ].getTrack().erase( towers[ ( dragblock->getColumn() - 1 ) ].getTrack().begin() );
                            towers[i].getBlocks()[0].getBlock().setPosition( blockposition( towers[i].getBlocks()[0].getBlocknum(), i + 1, param1, totBlocks, towers[i].getBlocks().size() ) );
                            cout<<"Blockexecuted";
                            break;
                            //checkhover1 = true;
                            //if( towers[i].getBlockTrack() > )
                        }
                        else if( i == 2 ){
                            dragblock->getBlock().setPosition( initPosition );
                        }
                    }
                    //if( )
                }
                dragblock = nullptr;
                mousehold = false;
                cout<<"Released";
            }
        }
        //towers[1].getHanoiBlock(1).getBlock().
        if( sf::Mouse::isButtonPressed( sf::Mouse::Button::Left ) ){
            //sf::Mouse::setPosition( { 0, 0 } );
            if( buttonpressed == false ){
                buttonpressed = true;
                dtclock.restart().asMilliseconds();
                cout<<"Cycle executed";
            }
            else if( mousehold == true ){
                //dragblock = checkhanoihover( towers );
                if( dragblock != nullptr ){
                    dragblock->getBlock().setPosition( { static_cast<float>( window1.mapPixelToCoords( sf::Mouse::getPosition( window1 ) ).x ), static_cast<float>( window1.mapPixelToCoords( sf::Mouse::getPosition( window1 ) ).y ) } );
                }
            }
            else if( buttonpressed == true && dtclock.getElapsedTime().asMilliseconds() > 1000 && ( mousehold == false ) ){
                mousehold = true;
                //cout<<"\n\nDragPrecheck";
                dragblock = checkhanoihover( towers, window1 );
                if( dragblock != nullptr ){
                    initPosition = dragblock->getBlock().getPosition();
                }
                //cout<<"\n\nPostcheck";
                //cout<<"mousehold true";
            }

        }
        //window1.display();
    }
    
}
sf::Vector2f blockposition( int blocknum, int column, windowparams &param1, int totBlocks, int position1 ){
    sf::Vector2f temp( static_cast<float>(column * param1.hanoiDistance - ( blockwidthcomputation( blocknum, param1, totBlocks ) / 2 ) ), static_cast<float>( param1.towDimensions.towerBase - ( position1 ) * param1.blockdimensions.blockHeight ) );
    return temp;

}
float blockwidthcomputation( int blocknum1, windowparams &param1, int totBlocks ){
    float blockwidth = ( param1.blockdimensions.maxBlockWidth - param1.blockdimensions.minBlockWidth ) / ( totBlocks - 1 ) * ( blocknum1 ) + param1.blockdimensions.minBlockWidth;
    //cout<<"\n\n"<<blocknum1<<endl;
    return blockwidth;
}
hanoiblock* checkhanoihover( std::vector<hanoiTowers>& towers, sf::RenderWindow &window1 ){
    //hanoiblock 
    hanoiblock* pointerblock = nullptr;
    for( int i = 0; i < 3; i++ ){
        if( towers[i].getBlocks().size() != 0 ){
            if( checkhover( towers[i].getHanoiBlock(0).getBlock(), window1.mapPixelToCoords( sf::Mouse::getPosition( window1 ) ) ) ){
                pointerblock = &(towers[i].getHanoiBlock(0));
                break;
            }
        }
        //else if( i == 2 ){
        //    return nullptr;
        //}
    }
    return pointerblock;
}
bool checkhover( sf::RectangleShape block, sf::Vector2f point ){
    if( point.x > block.getPosition().x && point.x < ( block.getPosition().x + block.getSize().x ) ){
        if( point.y > block.getPosition().y && point.y < ( block.getPosition().y + block.getSize().y ) ){
            return true;
        }
        else{
            return false;
        }
    }
    else{
        return false;
    }
}
sf::Vector2f getcenterpoint( sf::RectangleShape &shape1 ){
    return { ( shape1.getPosition().x + shape1.getSize().x / 2 ), ( shape1.getPosition().y + shape1.getSize().y / 2 ) };
}