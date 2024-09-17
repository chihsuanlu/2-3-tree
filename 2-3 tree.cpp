#include <iostream> 
#include <fstream> 
#include <string> 
#include <vector> 
#include <cstdlib> 
#include <iomanip> 
#include <ctime> 
#include <cmath>
#include <iomanip>

using namespace std;

struct Data { 
	string rawR; 
 	string cname;
 	string dnum;
	string dname; 
	string day;
 	string up;
 	string sNO; 
 	string tNO;
 	string gNO; 
 	string city;
 	string t;
	int num;
	bool splitt;
	
}; 

struct node23 {
	vector<Data> name[3];
	node23 *child[4]; 
	bool full;
};

struct nodeAVL {
	vector<Data> value;
	nodeAVL *l;
	nodeAVL *r;
	int height;
};


class twothreeTree {
	public:
		
		int treeH ;
		
		int getnum( string item ) {      //防呆 以防字串出現"" 
			int ans = 0 ;
			for ( int i = 0 ; i < item.size() ; i++ ) {
				if ( isdigit( item[i] ) == true ) 
					ans = ans*10 + (item[i]-'0');
 			}
 			return ans;
		}
		
		bool readFile( string name ) {
			ifstream file;
			file.open( name.c_str() );
			
			if(file.is_open())	
				return true;
			else{
				cout << endl<< "### " << name << " does not exist! ###" << endl ;
				return false;
			}
			file.close();
		} 
		
		
		bool isleaf ( struct node23 *tree ) {
     		for(int i = 0; i < 4; ++i){
        		if( tree->child[i] != NULL )
        			return false;
			}
			return true;
		}
		
		int getH( struct node23 *cur, int level ) {                    
    		if ( cur != NULL ) {
    		    if ( level > treeH )  treeH = level;                         
    		    getH ( cur->child[0], level+1 );                                
     			for (int i = 0; i < 4 ; i++) {                          
        		    if ( !cur->name[i].size() )                         
                		break;                                          
        		    getH(cur->child[i+1], level+1);
        		}  
    		}   
    		return treeH;
		}   
		
		int nodeNum23( struct node23 *root ){
			if ( root == NULL )
				return 0;
			else 
				return nodeNum23( root->child[0] ) + nodeNum23( root->child[1] ) + nodeNum23( root->child[2] ) + 1 ;	
		}
		
		void printAns ( struct node23 *tree ) {                                      // print Ans  
			
			if( tree->name[1].size() != 0 ){
				if( tree->name[1][0].num <  tree->name[0][0].num ){
					for ( int i = 0 ; i < tree->name[1].size() ; i++ ){
						cout << i+1 << ": [" << tree->name[1][i].num << "] " << tree->name[1][i].cname << ", " << tree->name[1][i].dname 
						<< ", " << tree->name[1][i].day << ", " << tree->name[1][i].up << ", " << getnum( tree->name[1][i].gNO ) << endl;
					}
					for ( int i = 0 ; i < tree->name[0].size() ; i++ ){
						cout << i+tree->name[1].size()+1 << ": [" << tree->name[0][i].num << "] " << tree->name[0][i].cname << ", " 
						<< tree->name[0][i].dname << ", " << tree->name[0][i].day << ", " << tree->name[0][i].up << ", " << getnum( tree->name[0][i].gNO ) << endl;
					}
				}
				else {
					for ( int i = 0 ; i < tree->name[0].size() ; i++ ){
						cout << i+1 << ": [" << tree->name[0][i].num << "] " << tree->name[0][i].cname << ", " << tree->name[0][i].dname 
						<< ", " << tree->name[0][i].day << ", " << tree->name[0][i].up << ", " << getnum( tree->name[0][i].gNO ) << endl;
					}
					for ( int i = 0 ; i < tree->name[1].size() ; i++ ){
						cout << i+1+tree->name[0].size() << ": [" << tree->name[1][i].num << "] " << tree->name[1][i].cname << ", " 
						<< tree->name[1][i].dname << ", " << tree->name[1][i].day << ", " << tree->name[1][i].up << ", " << getnum( tree->name[1][i].gNO ) << endl;
					}
				}
			}
			else {
				for ( int i = 0 ; i < tree->name[0].size() ; i++ ){
					cout << i+1 << ": [" << tree->name[0][i].num << "] " << tree->name[0][i].cname << ", " << tree->name[0][i].dname 
					<< ", " << tree->name[0][i].day << ", " << tree->name[0][i].up << ", " << getnum( tree->name[0][i].gNO ) << endl;
				}
			}
		}
		
		void split( struct node23 *&root ){
			if ( root == NULL )
				return;
				
			node23 *nnode = new node23;                                   
			nnode->name[0] = root->name[2];                     //         [2]      
			                                                    //        /   \
			                                                    //      [0]   [1]
			nnode->child[0] = new node23;                       
			nnode->child[1] = new node23;
			nnode->child[2] = new node23;
			nnode->child[3] = new node23;
			
			nnode->child[1] = NULL;
			nnode->child[3] = NULL;
			nnode->child[0]->name[0] = root->name[0];
			nnode->child[2]->name[0] = root->name[1];
			
			
 			nnode->child[0]->child[0] = root->child[0];
 			nnode->child[0]->child[2] = root->child[1]; 			
			nnode->child[0]->child[1] = NULL;
			nnode->child[0]->child[3] = NULL;
			
			nnode->child[2]->child[0] = root->child[2];
			nnode->child[2]->child[2] = root->child[3];
			nnode->child[2]->child[1] = NULL;
			nnode->child[2]->child[3] = NULL;
		
			root = nnode;
			root->full = false;
			root->child[0]->full = false;
			root->child[2]->full = false;
	
			root->name[0][0].splitt = true;	
			root->child[0]->name[0][0].splitt = false;
			root->child[2]->name[0][0].splitt = false;

			nnode = NULL;
			return ;
		}
		 
		
		node23 *insert( vector<struct Data> &data, int i, struct node23 *&tree ){
			
			node23 *temp;
			if ( tree == NULL ) {
				tree = new node23;
				tree->name[0].push_back(data[i]);
				tree->child[0] = NULL;
				tree->child[1] = NULL;
				tree->child[2] = NULL;
				tree->child[3] = NULL;
				tree->full = false;
				return tree;
			}	
			
			for( int j = 0 ; j < 2 ; j++ ) {                                          // 相同學校名稱就拍拍屁股走人 
				if ( tree->name[j].size() != 0 ) {
					if ( data[i].cname == tree->name[j][0].cname ) {
						tree->name[j].push_back( data[i] );
						return tree;
					}
				}
			}
			
			if ( !isleaf( tree ) ){                                                   // not leaf !!!!!!!!
			             
				if ( data[i].cname < tree->name[0][0].cname )                         // go left
					temp = insert( data, i, tree->child[0] );
				else {
					if ( tree->name[1].size() != 0 && data[i].cname < tree->name[1][0].cname )                 // go middle
						temp = insert( data, i, tree->child[1]);
					else 
						temp = insert( data, i, tree->child[2]);                                               // go right
				}
			
				if ( temp->name[0][0].splitt == true ) {                                                       // 回傳的temp做過分裂 再判斷上去 
					if ( tree->full== false ){                                                                 // split後回傳的節點 是否也滿了 
						if ( temp->name[0][0].cname > tree->name[0][0].cname ){
							tree->name[1] = temp->name[0]; 
							tree->child[1] = temp->child[0]; 
							tree->child[2] = temp->child[2];                                                   // 沒滿的話放上去就好 :D 
							tree->child[3] = NULL;
						}
						else if ( temp->name[0][0].cname < tree->name[0][0].cname ){
							tree->name[1] = tree->name[0];
							tree->name[0] = temp->name[0];
							tree->child[0] = temp->child[0];
							tree->child[1] = temp->child[2];
							tree->child[3] = NULL;
						}
						
						tree->full = true;
						tree->name[0][0].splitt = false;
						return tree;
					}
					else {                                                                                     // 回傳的節點也滿了 !! 
							
						if ( temp->name[0][0].cname > tree->name[1][0].cname ){
							tree->name[2] = tree->name[1];
							tree->name[1] = temp->name[0];
							
							tree->child[0] = tree->child[0];
							tree->child[1] = tree->child[1];
							tree->child[2] = temp->child[0];
							tree->child[3] = temp->child[2];
						}
						else if ( temp->name[0][0].cname < tree->name[0][0].cname ){                          // 將其節點和回傳節點結合
						                                                                                      //並設定好相對應的子節點
							tree->name[2] = tree->name[0];
							tree->name[0] = temp->name[0];
							
							tree->child[3] = tree->child[2];
							tree->child[2] = tree->child[1];
							tree->child[0] = temp->child[0];
							tree->child[1] = temp->child[2];
						}
						else {
							tree->name[2] = temp->name[0];
							
							tree->child[0] = tree->child[0];
							tree->child[3] = tree->child[2];
							tree->child[1] = temp->child[0];
							tree->child[2] = temp->child[2];	
						}	
						split( tree );                                                                          // split recursion !!! :D 
						return tree;
					}
					
					return tree;
				}
				return tree;	
			}
			
			else {                                                                                              // if is leaf 
				if ( tree->full == false ) {
					if ( data[i].cname > tree->name[0][0].cname )
						tree->name[1].push_back( data[i] );
						
					else if ( data[i].cname < tree->name[0][0].cname ) {
						tree->name[1].push_back( data[i] );
						swap( tree->name[1], tree->name[0] );
					}
					
					tree->full = true;
					return tree;
				}
				else {
					tree->name[2].push_back( data[i] );
					if ( data[i].cname < tree->name[0][0].cname )
						swap( tree->name[2], tree->name[0] );
					else if ( data[i].cname > tree->name[1][0].cname )
						swap( tree->name[2], tree->name[1] );
												
					split( tree );
					return tree;
				}
			}
				
			return tree;
		}
		
		void buildTree23( string name, vector<struct Data> &data, struct node23 *tree ) {
			// 將檔案存入vector 
			string t;
			int n = 0 ;
			ifstream file;
			file.open( name.c_str() );
			getline(file, t);
			getline(file, t);
			getline(file, t);
			while ( getline(file, t))
				n++;
			file.close();
			file.open( name.c_str() );
			getline(file, t);
			getline(file, t);
			getline(file, t);
			
			for ( int i = 0 ; i < n ; i++ ) {
					
				Data temp;
				temp.num = i+1 ;
				getline( file, temp.rawR, '\t' ); 		
				getline( file, temp.cname, '\t' ); 		
				getline( file, temp.dnum, '\t' ); 		
				getline( file, temp.dname, '\t' ); 		
				getline( file, temp.day, '\t' ); 				
				getline( file, temp.up, '\t' ); 		 		
				getline( file, temp.sNO, '\t' ); 		
				getline( file, temp.tNO, '\t' ); 		
				getline( file, temp.gNO, '\t' ); 				
				getline( file, temp.city, '\t' ); 		
				getline( file, temp.t, '\n' ); 	
					
				data.push_back(temp);
				data[i].splitt = false;
				tree = insert( data, i, tree ) ;                                         // 一筆一筆新增 !!!! :D 
			}
			
			file.close();
			treeH = 0;
			cout << "Tree hights = " << getH( tree, 0 ) + 1   << endl ;
			cout << "Number of nodes = " << nodeNum23( tree ) <<  endl;
			printAns( tree );
			
		}
		
		
}; 


class AVL : public twothreeTree {
	
	public:
		int nodeNumAVL( struct nodeAVL *root ){
			if ( root == NULL )
				return 0;
			else 
				return nodeNumAVL( root->l ) + nodeNumAVL( root->r ) + 1 ;	
		}
		
		int height( struct nodeAVL *node ){
			if( node == NULL )
				return 0;
			else{
				int left;
				int right;
				left = height( node -> l );
				right = height( node -> r );
				if( left > right )
					return left + 1 ;
				else
					return right + 1;
			}
	    }
	    
	    int BF( struct nodeAVL *node ){
	    	if (node == NULL)
      		  return 0;
    		return height( node->l ) - height( node->r );
		}
			
		nodeAVL *LL( struct nodeAVL *x ) {
			nodeAVL *y = new nodeAVL;
			y = x->l;
			x->l = y->r;
			y->r = x;
			return y;
		}
			
		nodeAVL *RR( struct nodeAVL *x ) {
			nodeAVL *y = new nodeAVL;
			y = x->r;
			x->r = y->l;
			y->l = x;
			return y;
		}
			
		nodeAVL *LR( struct nodeAVL *x ) {
			x->l = RR( x->l );
			return LL( x );
		}
		
		nodeAVL *RL( struct nodeAVL *x ) {
			x->r = LL( x->r );
			return RR( x );
		}
			
		nodeAVL *insertAVL( vector<struct Data> &data, int i, struct nodeAVL *&tree ) {
			
			if ( tree == NULL ) {
				tree = new nodeAVL;
				tree->value.push_back(data[i]);
				tree->l = NULL;
				tree->r = NULL;
				tree->height = 1;
				return tree;
			}
					
			if ( getnum( data[i].gNO ) == getnum( tree->value[0].gNO ) ) {
				tree->value.push_back( data[i] );
				return tree;
			}
			
			else{
				if ( getnum(data[i].gNO) < getnum(tree->value[0].gNO) )
					tree->l = insertAVL( data, i, tree->l );
				else 
					tree->r = insertAVL( data, i, tree->r );
			}
				
			tree->height = height( tree );
			
			if ( BF( tree ) == 2 ) {
				if ( BF( tree->l ) == -1 ) 	
					tree = LR( tree );	
				else if ( BF( tree->l ) == 1 || BF( tree->l ) == 0 ) 
					tree = LL( tree );					
			}
				
			else if ( BF( tree ) == -2 ) {
				if ( BF( tree->r ) == 1 ) 
					tree = RL( tree );
				else if ( BF( tree->r ) == -1 || BF( tree->r ) == 0  ) 
					tree = RR( tree );	
			}
			return tree;
		}
			
		void buildTreeAVL( string name, vector<struct Data> &data, struct nodeAVL *&tree ) {
			string t;
			int n = 0 ;
			ifstream file;
			file.open( name.c_str() );
			getline(file, t);
			getline(file, t);
			getline(file, t);
			while ( getline(file, t))
				n++;
			file.close();
			file.open( name.c_str() );
			getline(file, t);
			getline(file, t);
			getline(file, t);
			
			for ( int i = 0 ; i < n ; i++ ) {
				Data temp;
				temp.num = i+1 ;
				getline( file, temp.rawR, '\t' ); 		
				getline( file, temp.cname, '\t' ); 		
				getline( file, temp.dnum, '\t' ); 		
				getline( file, temp.dname, '\t' ); 		
				getline( file, temp.day, '\t' ); 				
				getline( file, temp.up, '\t' ); 		 		
				getline( file, temp.sNO, '\t' ); 		
				getline( file, temp.tNO, '\t' ); 		
				getline( file, temp.gNO, '\t' ); 				
				getline( file, temp.city, '\t' ); 		
				getline( file, temp.t, '\n' ); 	
				data.push_back(temp);
				tree = insertAVL( data, i, tree ) ;
			}
	
			file.close();		
			cout << "Tree hights = " << height( tree ) << endl ;
			cout << "Number of nodes = " << nodeNumAVL( tree ) <<  endl;
			for ( int i = 0 ; i < tree->value.size() ; i++ )
				cout << i+1 << ": [" << tree->value[i].num << "] " << tree->value[i].cname << ", " << tree->value[i].dname 
				<< ", " << tree->value[i].day << ", " << tree->value[i].up << ", " << getnum( tree->value[i].gNO ) << endl;
				
		}
		
		
		void search( struct nodeAVL *root, int  &n, int &no ) {
	    	if ( root == NULL  ){
				return ;
			}
			
			if ( n > 0 ) {
				search( root->r, n , no)  ;
				if ( n > 0 ) {
					for ( int i = 0 ; i < root->value.size() ; i++ ) {
						cout << no << ": [" << root->value[i].num << "] " << root->value[i].cname << ", " << root->value[i].dname 
						<< ", " << root->value[i].day << ", " << root->value[i].up << ", " << getnum( root->value[i].gNO ) << endl;
						no++;
						n--;
					}
				}
				
				
				search( root->l, n, no );
			}
			else 
				return;
			
		}
		
	
	
};

int main(void){ 
	int command = 0; // user command
	string name;
	string temp;
	vector<Data> data ;
	vector<Data> dataAVL ;
	twothreeTree Tree23;
	node23 *tree23;
	int k;
	int no;
	nodeAVL *treeAVL;
	tree23 = NULL;
	treeAVL = NULL;

	AVL avl;
	
	do{
		cout << endl << "*** Search Tree Utilities **";
 		cout << endl << "* 0. QUIT                  *";
 		cout << endl << "* 1. Build 2-3 tree        *";
 		cout << endl << "* 2. Build AVL tree        *";
 		cout << endl << "** 3. Top-K search on AVL tree *"; 		
 		cout << endl << "*************************************";
 		
		cout << endl << "Input a command(0, 1, 2, 3): ";
 		cin >> command; // get the command
 		
 		switch (command){ 
 			
			case 0: 
				break;
 			case 1: 
 				
 				cout << endl << "Input a file number [0: quit]:"  ;
 				cin >> temp;
 				name = "input";
   	  		    name = name + temp;
   	  		   	name = name + ".txt";
   	  		   	if (temp == "0") break;
   	  		   	while ( Tree23.readFile( name ) == false ){
   					cout << endl << "Input a file number [0: quit]:"  ;
   					cin >> temp;
   					if (temp == "0") break;
					name = "input";
   	  		  		name = name + temp;
   	  		    	name = name + ".txt";	
				}
				if ( temp == "0" ) break;
				tree23 = NULL;
				data.clear();
				Tree23.buildTree23( name, data, tree23 );
 				break;
 				
 			case 2:
 				
 				cout << endl << "Input a file number [0: quit]:"  ;
 				cin >> temp;
 				name = "input";
   	  		    name = name + temp;
   	  		   	name = name + ".txt";
   	  		   	if (temp == "0") break;
   	  		   	while ( avl.readFile( name ) == false ){
   					cout << endl << "Input a file number [0: quit]:"  ;
   					cin >> temp;
   					if (temp == "0") break;
					name = "input";
   	  		  		name = name + temp;
   	  		    	name = name + ".txt";	
				}
				if ( temp == "0" ) break;
				treeAVL = NULL;
				dataAVL.clear();
				avl.buildTreeAVL( name, dataAVL, treeAVL );
				break;
			case 3:
				no = 1 ;
				if ( treeAVL != NULL ) {
					cout << endl << "Enter K in [1," << dataAVL.size() << "] : " ;
					cin >> k ;
					avl.search( treeAVL, k, no);
				}
				else 
					cout << "### Choose 2 first. ###" << endl;
				
 				
				break;
			
			
			default: cout << endl << "Command does not exist!" << endl;
 		} 
 	} while (command != 0); 
 	return 0;
} 
