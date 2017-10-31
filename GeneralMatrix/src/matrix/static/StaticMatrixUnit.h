/*
 * StaticMatrixUnit.h
 *
 *  Created on: 2017Äê4ÔÂ5ÈÕ
 *      Author: looke
 */

#ifndef MATRIX_STATIC_STATICMATRIXUNIT_H_
#define MATRIX_STATIC_STATICMATRIXUNIT_H_

#include "basic\BasicMatrix.h"
/*
#include "static\static1510\Static1510Matrix.h"
#include "static\static1511\Static1511Matrix.h"
#include "static\static1015\Static1015Matrix.h"
#include "static\static1010\Static1010Matrix.h"
#include "static\static1111\Static1111Matrix.h"
#include "static\static1115\Static1115Matrix.h"
#include "static\static1515\Static1515Matrix.h"
#include "static\static44\Static44Matrix.h"
#include "static\static33\Static33Matrix.h"
#include "static\static32\Static32Matrix.h"
#include "static\static23\Static23Matrix.h"
#include "static\static22\Static22Matrix.h"
*/
class StaticMatrixUnit
{
public:
	StaticMatrixUnit();

	void init(int row, int column);
	//void reload(int row, int column);

	BasicMatrix* getCurrentMatrixPointer();

private:
	int rowNum;
	int columnNum;
	void setMatrixPointer(int row, int column);
	BasicMatrix* p_currentMatrix;
/*
	Static1511Matrix opMatrix_1511;
	Static1510Matrix opMatrix_1510;
	Static1015Matrix opMatrix_1015;
	Static1515Matrix opMatrix_1515;
	Static1111Matrix opMatrix_1111;
	Static1115Matrix opMatrix_1115;
	Static1010Matrix opMatrix_1010;
	Static44Matrix opMatrix_44;
	Static33Matrix opMatrix_33;
	Static32Matrix opMatrix_32;
	Static23Matrix opMatrix_23;
	Static22Matrix opMatrix_22;
*/
};


#endif /* MATRIX_STATIC_STATICMATRIXUNIT_H_ */
