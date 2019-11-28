#include <iostream>
#include <Eigen/Core>
#include <Eigen/Dense>

using namespace Eigen;
using namespace std;

// map 和 vector 的配合怎样的改变 矩阵的形状。
// 使用map 来从已有内存获得数据 形成一个vector
typedef Eigen::Map<Eigen::VectorXi> VectorRef;
// 使用map 来从已有的内存获得数据形成一个vector （const）
typedef Eigen::Map<const Eigen::VectorXi> ConstVectorRef;

int main(){
	int num = 11;

	int array[num];
	// 首先定义一个数组
	for(int i = 0; i < num; ++i) array[i] = i;
	// 从array的第一个内存开始把数据映射为一个vector
	cout << "VectorRef:\n" << VectorRef(array,7) << endl;  
	/* output
	VectorRef:
	0
	1
	2
	3
	4
	5
	6
	 */
	// 从array的第二个内存开始把数据映射为一个vector
	cout << "VectorRef:\n" << VectorRef(array+1,7) << endl;
	/* VectorRef:
	1
	2
	3
	4
	5
	6
	7 */
	// 从array的第一个内存开始把数据映射为一个const vector
	// cout << "ConstVectorRef :\n" << ConstVectorRef(array,4) << endl;

	VectorRef testvector(array,3);
	cout << "testvector :\n" << testvector << endl;
	/* testvector :
	0
	1
	2 */

	ConstVectorRef testconstvector(array,4);
	cout << "testconstvector :\n" << testconstvector << "\n";
	cout << "testconstvector.size(): " << testconstvector.size()  << endl;
	/* testconstvector :
	0
	1
	2
	3
	testconstvector.size(): 4

 	*/
 
 	// testconstvector[2] = 4; 
	// 	 error: lvalue required as left operand of assignment


	cout << "Column-major-12:\n" << Map<Matrix<int,2,6> >(array) << endl;
	/* 
	Column-major-12:
	0  2  4  6  8 10
	1  3  5  7  9  0 */

	cout << "Column-major:\n" << Map<Matrix<int,2,4> >(array) << endl;
	/* Column-major:
	0 2 4 6
	1 3 5 7
	 */
	 
	cout << "Row-major:\n" << Map<Matrix<int,2,4,RowMajor> >(array) << endl;
	/* Row-major:
	0 1 2 3
	4 5 6 7 */
	 
	cout << "Row-major using stride:\n" <<
	 
	Map<Matrix<int,2,4>, Unaligned, Stride<1,5> >(array) << endl;
	/* Row-major using stride:
	0 1 2 3
	5 6 7 8 */
}
