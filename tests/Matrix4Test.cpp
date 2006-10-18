#include "Matrix4Test.h"
#include <iostream>

using namespace std;
namespace vmml
{

Matrix4Test::Matrix4Test()
    : ok ( true )
    , _matrix( 16., 2., 3., 13., 5., 11., 10., 8., 9., 7., 6., 12., 4., 14., 15., 1. )
{}

bool Matrix4Test::test()
{
    // ctor test
    Matrix4d tmatrix_test( 16., 2., 3., 13., 5., 11., 10., 8., 9., 7., 6., 12., 4., 14., 15., 1. );
    for ( size_t i = 0; i < 16; ++i )
    {
        if ( _matrix.ml[i] != tmatrix_test.ml[i] )
        {
            cout << "test: Matrix4::Matrix4( ... ) failed!" << endl;
            failed();
            assert( 0 );            
        }
    }
    // set test    
    _matrix.set( 1., 2., 3., 4., 5., 6., 7., 8., 9., 10., 11., 12., 13., 14., 15., 16. );
    tmatrix_test.set( 1., 2., 3., 4., 5., 6., 7., 8., 9., 10., 11., 12., 13., 14., 15., 16. );
    for ( size_t i = 0; i < 16; ++i )
    {
        if ( _matrix.ml[i] != tmatrix_test.ml[i] )
        {
            cout << "test: Matrix4::set( ... ) failed!" << endl;
            failed();
            assert( 0 );            
        }
    }
    // operator == / != test
    if ( _matrix != tmatrix_test )
    {
        cout << "test: Matrix4::operator ==() / !=() failed!" << endl;
        failed();
        assert( 0 );
    }  
 
    // transpose test
    Matrix4d tmatrix( 16., 2., 3., 13., 5., 11., 10., 8., 9., 7., 6., 12., 4., 14., 15., 1. );
    tmatrix_test.set( 16., 5., 9., 4., 2., 11., 7., 14., 3., 10., 6., 15., 13., 8., 12., 1. );
    Matrix4d tmatrix_T_Test = tmatrix.getTransposed();
    if (  tmatrix_test != tmatrix_T_Test )
    {
        cout << "test: Matrix4::transpose() failed!" << endl;
        failed();
        assert( 0 );
    }
    
    // get set column/row test
    Vector4d vrow( 1., 2., 3., 4. );
    _matrix.setRow( 0, vrow );
    for ( size_t i = 0; i < 4; i++ )
    {
        if ( _matrix.getElement( 0, i ) != vrow[i] )
        {
            cout << "test: Matrix4::setRow(...) failed!" << endl;
            failed();
            assert( 0 );       
        } 
    }
    
    Vector4d vrow_test = _matrix.getRow( 0 );
    if ( vrow != vrow_test )
    {
            cout << "test: Matrix4::getRow() failed!" << endl;
            failed();
            assert( 0 );       
    }
    
    _matrix.setColumn( 2, vrow);
    for ( size_t i = 0; i < 4; i++ )
    {
        if ( _matrix.getElement( i, 2 ) != vrow[i] )
        {
            cout << "test: Matrix4::setColumn(...) failed!" << endl;
            failed();
            assert( 0 );       
        } 
    }
    
    Vector4d col = _matrix.getColumn( 2 );
    {
        if ( vrow != col )
        {
            cout << "test: Matrix4::getColumn(...) failed!" << endl;
            failed();
            assert( 0 );       
        }
    }
    
    // misc operators 
    Matrix4d tm;
    tm = _matrix;
    if ( tm != _matrix )
    {
        cout << "test: Matrix4::operator=(...) failed!" << endl;
        failed();
        assert( 0 );           
    }

    tm *= 0.5f;
    for ( size_t i = 0; i < 9; ++i )
    {
        if ( tm.ml[i] != _matrix.ml[i] * 0.5f )
        {
            cout << "test: Matrix4::operator*=( scalar ) failed!" << endl;
            failed();
            assert( 0 );           
        }
    }
    Matrix4d tmm( _matrix );
    tmm = _matrix * 0.5f;
    if ( tmm != tm )
    {
        cout << "test: Matrix4::operator*( scalar ) failed!" << endl;
        failed();
        assert( 0 );           
    }
    
    _matrix.set( 17., 24., 1., 8., 23., 5., 7., 14., 4., 6., 13., 20., 10., 12., 19., 21. );
    tm.set( 16., 2., 3., 13., 5., 11., 10., 8., 9., 7., 6., 12., 4., 14., 15., 1. );
    tmm.set( 433., 417, 417, 433, 512, 346, 371, 437, 291, 445, 450, 276, 475, 579, 579, 475 );
    Matrix4d tmmm = _matrix * tm;
    if ( tmm != tmmm )
    {
        cout << "test: Matrix4::operator*( matrix ) failed!" << endl;
        cout << _matrix << tm << tmm << tmmm << endl;
        failed();
        assert( 0 );           
    }  
    
    tmmm = _matrix;
    tmmm *= tm;
    if ( tmm != tmmm )
    {
        cout << "test: Matrix4::operator*=( matrix ) failed!" << endl;
        cout << tmmm << endl;
        failed();
        assert( 0 );           
    }
    
    // negation
    _matrix.set( 16., 2., 3., 13., 5., 11., 10., 8., 9., 7., 6., 12., 4., 14., 15., 1. );
    for ( size_t i = 0; i < 16; ++i )
    {
        tm.ml[i] = _matrix.ml[i] * -1; 
    }
    if ( tm != - _matrix || tm != _matrix.negate() )
    {
        cout << "test: Matrix4::operator- / negate() failed!" << endl;
        failed();
        assert( 0 );           
    }
      
    // determinant
    _matrix.set( 17., 24., 1., 8., 23., 5., 7., 14., 4., 6., 13., 20., 10., 12., 19., 21. );
    float det = _matrix.getDeterminant();
    if ( det != 56225 )
    {
        cout << "test: Matrix4::determinant() failed!" << endl;
        cout << "det: " << det << " instead of 56225 " << endl;
        failed();
        assert( 0 );           
    }

    // inverse
    Matrix4d mm( 17., 24., 1., 8., 23., 5., 7., 14., 4., 6., 13., 20., 10., 12., 19., 21. );
    Matrix4d tmf( -5.780346820809248e-03, 4.962205424633170e-02, -4.811027123165852e-02, 1.493997332147622e-02, 
                4.277456647398844e-02, -3.797243219208537e-02, -1.013783903957314e-02, 1.867496665184526e-02, 
                -3.930635838150288e-02, -1.333926189417519e-02, -1.333036905291240e-01, 1.508225878168074e-01, 
                1.387283236994219e-02, 1.013783903957314e-02, 1.493108048021343e-01, -1.066251667407737e-01 );
    bool isInvertible;
    Matrix4d invm = mm.getInverse( isInvertible );
    if ( tmf != invm )
    {
        Matrix4d dif = invm - tmf;
        // this is required since the inverse test might fail because of rounding errors.
        bool onlyRoundingError = true;
        for ( size_t i = 0; i < 16; ++i )
        {
            if ( invm.ml[i] - tmf.ml[i] > 1e-13 )
                onlyRoundingError = false;
        }
        if ( onlyRoundingError )
        {
        }
        else if ( ! isInvertible )
            cout << "... vmmlib mistakenly detects that test matrix is not invertible." << endl;
        else
        {
            cout << "test: Matrix4::inverse() failed!" << endl;
            cout << "result: " << invm << endl;
            cout << "corrent result: " << tmf << endl;
            cout << "difference matrix " << invm - tmf << endl;
            failed();
            assert( 0 );           
        }
    }
    
    // tensor product
    Vector4d u( 1, 2, 4, 9 );
    Vector4d v( 6, 3, 9, 7 );
    tm.tensor( u, v );
    for( int j = 0; j < 4; j++)
        for( int i = 0; i < 4; i++)
            tmm.m[i][j] = u[j] * v[i];
    if ( tm != tmm )
    {
        cout << "test: Matrix4::tensor() failed!" << endl;
        failed();
        assert( 0 );           
    }
    
    
    return ok;
}




}; // namespace vmml
