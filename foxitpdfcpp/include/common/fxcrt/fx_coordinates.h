/**
 * Copyright (C) 2003-2020, Foxit Software Inc..
 * All Rights Reserved.
 *
 * http://www.foxitsoftware.com
 *
 * The following code is copyrighted and is the proprietary of Foxit Software Inc.. It is not allowed to
 * distribute any parts of Foxit PDF SDK to third party or public without permission unless an agreement
 * is signed between Foxit Software Inc. and customers to explicitly grant customers permissions.
 *
 * @file fx_coordinates.h
 * @brief Header file for coordinate system.
 */

//<<<+++OPENSOURCE
//<<<+++OPENSOURCE_LICENSE
//<<<+++OPENSOURCE_BEGIN LIC==FOXIT||LIC==GOOGLE

/**
 * @addtogroup FXCRT
 * @{
 */

//<<<+++OPENSOURCE_MUST_BEGIN
#ifndef _FXCRT_COORDINATES_
#define _FXCRT_COORDINATES_
//<<<+++OPENSOURCE_MUST_END

//internal classes
template<class baseType> class CFX_PSVTemplate;
template<class baseType> class CFX_VTemplate;
template<class baseType> class CFX_PRLTemplate;
template<class baseType> class CFX_RTemplate;
template<class baseType> class CFX_ETemplate;
template<class baseType> class CFX_ATemplate;
template<class baseType> class CFX_RRTemplate;
class CFX_Matrix;

//*****************************************************************************
//* Point/Size
//*****************************************************************************
/** The class represents a template for a point on the plane.*/
template<class BaseType>
class CFX_PSVTemplate : public CFX_Object
{
 public:
  typedef CFX_PSVTemplate<BaseType>  FXT_PSV;
//  typedef CFX_PSVTemplate<baseType>  FXT_POINT;
//  typedef CFX_PSVTemplate<baseType>  FXT_SIZE;

  /** @brief Constructor. */
  CFX_PSVTemplate() : x(0), y(0) {}

  /**
   * @brief Constructor, with parameters.
   *
   * @param[in] new_x  x coordinate of the point.
   * @param[in] new_y  y coordinate of the point.
   */
  CFX_PSVTemplate(BaseType new_x, BaseType new_y) : x(new_x), y(new_y) {}

  /**
   * @brief Copy constructor.
   *
   * @param[in] other  Another object.
   */
  CFX_PSVTemplate(const CFX_PSVTemplate& other) : x(other.x), y(other.y) {}

  /**
   * @brief Set values.
   *
   * @param[in] x  x coordinate of the point.
   * @param[in] y  x coordinate of the point.
   *
   * @return None.
   */
  void    Set(BaseType x, BaseType y)      {FXT_PSV::x = x, FXT_PSV::y = y;}
  /**
   * @brief Set values.
   *
   * @param[in] psv  Another value object.
   *
   * @return None.
   */
  void    Set(const FXT_PSV &psv)        {FXT_PSV::x = psv.x, FXT_PSV::y = psv.y;}
  /**
   * @brief Add a point.
   *
   * @param[in] x  x coordinate of the subtrahend point.
   * @param[in] y  x coordinate of the subtrahend point.
   *
   * @return None.
   */
  void    Add(BaseType x, BaseType y)      {FXT_PSV::x += x, FXT_PSV::y += y;}
  /**
   * @brief Subtract a point.
   *
   * @param[in] x  x coordinate of the addend point.
   * @param[in] y  x coordinate of the addend point.
   *
   * @return None.
   */
  void    Subtract(BaseType x, BaseType y)  {FXT_PSV::x -= x, FXT_PSV::y -= y;}
  /**
   * @brief Reset to the base point.
   *
   * @return None.
   */
  void    Reset()                {FXT_PSV::x = FXT_PSV::y = 0;}

  /**
   * @brief Overload operator +=.
   *
   * @param[in] obj  Another value object.
   *
   * @return A reference to current object itself.
   */
  FXT_PSV&  operator += (const FXT_PSV &obj)  {x += obj.x; y += obj.y; return *this;}
  /**
   * @brief Overload operator -=.
   *
   * @param[in] obj  Another value object.
   *
   * @return A reference to current object itself.
   */
  FXT_PSV&  operator -= (const FXT_PSV &obj)  {x -= obj.x; y -= obj.y; return *this;}
  /**
   * @brief Overload operator *=.
   *
   * @param[in] lamda  A value to be multiplied.
   *
   * @return A reference to current object itself.
   */
  FXT_PSV&  operator *= (BaseType lamda)    {x *= lamda; y *= lamda; return *this;}
  /**
   * @brief Overload operator /=.
   *
   * @param[in] lamda  A value to be divided.
   *
   * @return A reference to current object itself.
   */
  FXT_PSV&  operator /= (BaseType lamda)    {x /= lamda; y /= lamda; return *this;}

  /**
   * @brief Overload operator ==.
   *
   * @param[in] obj1  First value object.
   * @param[in] obj2  Second value object.
   *
   * @return <b>true</b> means input value objects are equal, while <b>false</b> means not equal.
   */
  friend  FX_BOOL    operator == (const FXT_PSV &obj1, const FXT_PSV &obj2)  {return obj1.x == obj2.x && obj1.y == obj2.y;}
  /**
   * @brief Overload operator !=.
   *
   * @param[in] obj1  First value object.
   * @param[in] obj2  Second value object.
   *
   * @return <b>true</b> means input value objects are not equal, while <b>false</b> means equal.
   */
  friend  FX_BOOL    operator != (const FXT_PSV &obj1, const FXT_PSV &obj2)  {return obj1.x != obj2.x || obj1.y != obj2.y;}
  /**
   * @brief Overload operator +.
   *
   * @param[in] obj1  First value object.
   * @param[in] obj2  Second value object.
   *
   * @return A value object as result.
   */
  friend  FXT_PSV    operator + (const FXT_PSV &obj1, const FXT_PSV &obj2)  {CFX_PSVTemplate obj; obj.x = obj1.x + obj2.x; obj.y = obj1.y + obj2.y; return obj;}
  /**
   * @brief Overload operator -.
   *
   * @param[in] obj1  First value object.
   * @param[in] obj2  Second value object.
   *
   * @return A value object as result.
   */
  friend  FXT_PSV    operator - (const FXT_PSV &obj1, const FXT_PSV &obj2)  {CFX_PSVTemplate obj; obj.x = obj1.x - obj2.x; obj.y = obj1.y - obj2.y; return obj;}
  /**
   * @brief Overload operator *.
   *
   * @param[in] obj  A value object.
   * @param[in] lamda  A value to multiply.
   *
   * @return A value object as result.
   */
  friend  FXT_PSV    operator * (const FXT_PSV &obj, BaseType lamda)      {CFX_PSVTemplate t; t.x = obj.x * lamda; t.y = obj.y * lamda; return t;}
  /**
   * @brief Overload operator *.
   *
   * @param[in] lamda  A value to multiply.
   * @param[in] obj  A value object to multiply.
   *
   * @return A value object as result.
   */
  friend  FXT_PSV    operator * (BaseType lamda, const FXT_PSV &obj)      {CFX_PSVTemplate t; t.x = lamda * obj.x; t.y = lamda * obj.y; return t;}
  /**
   * @brief Overload operator /.
   *
   * @param[in] obj  A value object.
   * @param[in] lamda  A value to be divided.
   *
   * @return A value object as result.
   */
  friend  FXT_PSV    operator / (const FXT_PSV &obj, BaseType lamda)      {CFX_PSVTemplate t; t.x = obj.x / lamda; t.y = obj.y / lamda; return t;}

  /** @brief x coordinate of the point.*/
  BaseType x;
  /** @brief y coordinate of the point.*/
  BaseType y;
};
/** @brief Type definition for point class for integer. */
typedef CFX_PSVTemplate<FX_INT32>           CFX_Point;
/** @brief Type definition for point class for float. */
typedef CFX_PSVTemplate<FX_FLOAT>           CFX_PointF;
/** @brief Type definition for size class for integer. */
typedef CFX_PSVTemplate<FX_INT32>           CFX_Size;
/** @brief Type definition for size class for float. */
typedef CFX_PSVTemplate<FX_FLOAT>           CFX_SizeF;
/** @brief Type definition for integer point array. */
typedef CFX_ArrayTemplate<CFX_Point>        CFX_Points;
/** @brief Type definition for float point array. */
typedef CFX_ArrayTemplate<CFX_PointF>       CFX_PointsF;
/** @brief Type definition for pointer to integer point. */
typedef CFX_PSVTemplate<FX_INT32> *         FX_LPPOINT;  
/** @brief Type definition for pointer to float point. */
typedef CFX_PSVTemplate<FX_FLOAT> *         FX_LPPOINTF;
/** @brief Type definition for constant pointer to integer point. */
typedef CFX_PSVTemplate<FX_INT32> const *   FX_LPCPOINT;
/** @brief Type definition for constant pointer to float point. */
typedef CFX_PSVTemplate<FX_FLOAT> const *   FX_LPCPOINTF;

//Keep old symbol
#define CFX_FloatPoint  CFX_PointF

/** The class represents vector template. */
template<class baseType>
class CFX_VTemplate: public CFX_PSVTemplate<baseType>
{
 public:
  typedef CFX_PSVTemplate<baseType>  FXT_PSV;
  typedef CFX_PSVTemplate<baseType>  FXT_POINT;
  typedef CFX_PSVTemplate<baseType>  FXT_SIZE;
  typedef CFX_VTemplate<baseType>    FXT_VECTOR;

  void    Set(baseType x, baseType y) {FXT_PSV::x = x, FXT_PSV::y = y;}
  void    Set(const FXT_PSV &psv)    {FXT_PSV::x = psv.x, FXT_PSV::y = psv.y;}
  void    Set(const FXT_POINT &p1, const FXT_POINT &p2)  {FXT_PSV::x = p2.x - p1.x, FXT_PSV::y = p2.y - p1.y;}
  void    Reset()            {FXT_PSV::x = FXT_PSV::y = 0;}

  baseType  SquareLength() const  {return FXT_PSV::x * FXT_PSV::x + FXT_PSV::y * FXT_PSV::y;}
  baseType  Length() const      {return FXSYS_sqrt(FXT_PSV::x * FXT_PSV::x + FXT_PSV::y * FXT_PSV::y);}
  void    Normalize()
  {
    FX_FLOAT fLen = FXSYS_sqrt(FXT_PSV::x * FXT_PSV::x + FXT_PSV::y * FXT_PSV::y);
    FXSYS_assert(fLen >= 0.0001f);
    if (fLen < 0.0001f)
      return;
    FXT_PSV::x = ((baseType)FXT_PSV::x) / fLen;
    FXT_PSV::y = ((baseType)FXT_PSV::y) / fLen;
  }
  baseType  DotProduct(baseType x, baseType y) const    {return FXT_PSV::x * x + FXT_PSV::y * y;}
  baseType  DotProduct(const FXT_VECTOR &v) const      {return FXT_PSV::x * v.x + FXT_PSV::y * v.y;}
  FX_BOOL    IsParallel(baseType x, baseType y) const    {baseType t = FXT_PSV::x * y - FXT_PSV::y * x; return FXSYS_fabs(t) < 0.0001f;}
  FX_BOOL    IsParallel(const FXT_VECTOR &v) const      {return IsParallel(v.x, v.y);}
  FX_BOOL    IsPerpendicular(baseType x, baseType y) const  {baseType t = DotProduct(x, y); return FXSYS_fabs(t) < 0.0001f;}
  FX_BOOL    IsPerpendicular(const FXT_VECTOR &v) const    {return IsPerpendicular(v.x, v.y);}

  void    Translate(baseType dx, baseType dy) {FXT_PSV::x += dx, FXT_PSV::y += dy;}
  void    Scale(baseType sx, baseType sy) {FXT_PSV::x *= sx, FXT_PSV::y *= sy;}
  void    Rotate(FX_FLOAT fRadian)
  {
    FX_FLOAT xx = (FX_FLOAT)FXT_PSV::x;
    FX_FLOAT yy = (FX_FLOAT)FXT_PSV::y;
    FX_FLOAT cosValue = FXSYS_cos(fRadian);
    FX_FLOAT sinValue = FXSYS_sin(fRadian);
    FXT_PSV::x = xx * cosValue - yy * sinValue;
    FXT_PSV::y = xx * sinValue + yy * cosValue;
  }

  friend  FX_FLOAT  Cosine(const FXT_VECTOR &v1, const FXT_VECTOR &v2)
  {
    FXSYS_assert(v1.SquareLength() != 0 && v2.SquareLength() != 0);
    FX_FLOAT dotProduct = v1.DotProduct(v2);
    return dotProduct / (FX_FLOAT)FXSYS_sqrt(v1.SquareLength() * v2.SquareLength());
  }
  friend  FX_FLOAT  ArcCosine(const FXT_VECTOR &v1, const FXT_VECTOR &v2)
  {
    return (FX_FLOAT)FXSYS_acos(Cosine(v1, v2));
  }
  friend  FX_FLOAT  SlopeAngle(const FXT_VECTOR &v)
  {
    CFX_VTemplate vx;
    vx.Set(1, 0);
    FX_FLOAT fSlope = ArcCosine(v, vx);
    return v.y < 0 ? -fSlope : fSlope;
  }
};

/** @brief Vector class for integer. */
typedef CFX_VTemplate<FX_INT32> CFX_Vector;
/** @brief Vector class for float. */
typedef CFX_VTemplate<FX_FLOAT> CFX_VectorF;

/** The class represents Parallelogram template. */
template<class baseType>
class CFX_PRLTemplate: public CFX_Object
{
 public:
  typedef CFX_PSVTemplate<baseType>  FXT_POINT;
  typedef CFX_PSVTemplate<baseType>  FXT_SIZE;
  typedef CFX_VTemplate<baseType>    FXT_VECTOR;
  typedef CFX_PRLTemplate<baseType>  FXT_PARAL;

  void  Set(baseType x, baseType y, baseType x1, baseType y1, baseType x2, baseType y2) {FXT_PARAL::x = x, FXT_PARAL::y = y, FXT_PARAL::x1 = x1, FXT_PARAL::y1 = y1, FXT_PARAL::x2 = x2, FXT_PARAL::y2 = y2;}
  void  Set(const FXT_POINT &p, const FXT_VECTOR &v1, const FXT_VECTOR &v2) {FXT_PARAL::P(p), FXT_PARAL::V1(v1), FXT_PARAL::V2(v2);}
  void  Reset()            {FXT_PARAL::x = FXT_PARAL::y = FXT_PARAL::x1 = FXT_PARAL::y1 = FXT_PARAL::x2 = FXT_PARAL::y2 = 0;}

  CFX_PRLTemplate&  operator += (const FXT_POINT &p) {x += p.x; y += p.y; return *this;}
  CFX_PRLTemplate&  operator -= (const FXT_POINT &p) {x -= p.x; y -= p.y; return *this;}

  FXT_POINT  P() const      {FXT_POINT p; p.x = x, p.y = y; return p;}
  void    P(FXT_POINT p)    {x = p.x, y = p.y;}
  FXT_VECTOR  V1() const      {FXT_VECTOR v; v.x = x1, v.y = y1; return v;}
  void    V1(FXT_VECTOR v)  {x1 = v.x, y1 = v.y;}
  FXT_VECTOR  V2() const      {FXT_VECTOR v; v.x = x2, v.y = y2; return v;}
  void    V2(FXT_VECTOR v)  {x2 = v.x, y2 = v.y;}

  FX_BOOL    IsEmpty() const  {return V1().IsParallel(x2, y2);}
  FX_BOOL    IsRect() const  {return V1().IsPerpendicular(x2, y2);}
  FXT_SIZE  Size() const  {FXT_SIZE s; s.x = V1().Length(); s.y = V2().Length(); return s;}
  FXT_POINT  Center() const  {return (V1() + V2()) / 2 + P();}
  FXT_POINT  P1() const    {return P();}
  FXT_POINT  P2() const    {return P() + V1();}
  FXT_POINT  P3() const    {return P() + V1() + V2();}
  FXT_POINT  P4() const    {return P() + V2();}

  baseType x, y;
  baseType x1, y1;
  baseType x2, y2;
};

/** @brief Type definition for parallelogram class for integer. */
typedef CFX_PRLTemplate<FX_INT32> CFX_Parallelogram;
/** @brief Type definition for parallelogram class for float. */
typedef CFX_PRLTemplate<FX_FLOAT> CFX_ParallelogramF;
//<<<+++OPENSOURCE_MUST_END

/** The class represents rectangle template. */
template<class baseType>
class CFX_RTemplate: public CFX_Object
{
 public:
  typedef CFX_PSVTemplate<baseType>  FXT_POINT;
  typedef CFX_PSVTemplate<baseType>  FXT_SIZE;
  typedef CFX_VTemplate<baseType>    FXT_VECTOR;
  typedef CFX_PRLTemplate<baseType>  FXT_PARAL;
  typedef CFX_RTemplate<baseType>    FXT_RECT;

  void    Set(baseType left, baseType top, baseType width, baseType height)  {FXT_RECT::left = left, FXT_RECT::top = top, FXT_RECT::width = width, FXT_RECT::height = height;}
  void    Set(baseType left, baseType top, const FXT_SIZE &size)        {FXT_RECT::left = left, FXT_RECT::top = top, FXT_RECT::Size(size);}
  void    Set(const FXT_POINT &p, baseType width, baseType height)      {TopLeft(p), FXT_RECT::width = width, FXT_RECT::height = height;}
  void    Set(const FXT_POINT &p1, const FXT_POINT &p2)            {TopLeft(p1), FXT_RECT::width = p2.x - p1.x, FXT_RECT::height = p2.y - p1.y, FXT_RECT::Normalize();}
  void    Set(const FXT_POINT &p, const FXT_VECTOR &v)            {TopLeft(p), FXT_RECT::width = v.x, FXT_RECT::height = v.y, FXT_RECT::Normalize();}
  void    Reset()                                {FXT_RECT::left = FXT_RECT::top = FXT_RECT::width = FXT_RECT::height = 0;}

  FXT_RECT&  operator += (const FXT_POINT &p) {left += p.x, top += p.y; return *this;}
  FXT_RECT&  operator -= (const FXT_POINT &p) {left -= p.x, top -= p.y; return *this;}

  baseType  right() const {return left + width;}
  baseType  bottom() const {return top + height;}
  void    Normalize() {if (width < 0) {left += width; width = -width;} if (height < 0) {top += height; height = -height;}}
  void    Offset(baseType dx, baseType dy) {left += dx; top += dy;}
  void    Inflate(baseType x, baseType y) {left -= x; width += x * 2; top -= y; height += y * 2;}
  void    Inflate(const FXT_POINT &p) {Inflate(p.x, p.y);}
  void    Inflate(baseType left, baseType top, baseType right, baseType bottom) {FXT_RECT::left -= left; FXT_RECT::top -= top; FXT_RECT::width += left + right; FXT_RECT::height += top + bottom;}
  void    Inflate(const FXT_RECT &rt) {Inflate(rt.left, rt.top, rt.left + rt.width, rt.top + rt.height);}
  void    Deflate(baseType x, baseType y) {left += x; width -= x * 2; top += y; height -= y * 2;}
  void    Deflate(const FXT_POINT &p) {Deflate(p.x, p.y);}
  void    Deflate(baseType left, baseType top, baseType right, baseType bottom) {FXT_RECT::left += left; FXT_RECT::top += top; FXT_RECT::width -= left + right; FXT_RECT::height -= top + bottom;}
  void    Deflate(const FXT_RECT &rt) {Deflate(rt.left, rt.top, rt.top + rt.width, rt.top + rt.height);}
  FX_BOOL    IsEmpty() const {return width <= 0 || height <= 0;}
  FX_BOOL    IsEmpty(FX_FLOAT fEpsilon) const {return width <= fEpsilon || height <= fEpsilon;}
  void    Empty() {width = height = 0;}
  FX_BOOL    Contains(baseType x, baseType y) const {return x >= left && x < left + width && y >= top && y < top + height;}
  FX_BOOL    Contains(const FXT_POINT &p) const {return Contains(p.x, p.y);}
  FX_BOOL    Contains(const FXT_RECT &rt) const {return rt.left >= left && rt.right() <= right() && rt.top >= top && rt.bottom() <= bottom();}
  baseType  Width() const {return width;}
  baseType  Height() const {return height;}
  FXT_SIZE  Size() const {FXT_SIZE size; size.Set(width, height); return size;}
  void    Size(FXT_SIZE s) {width = s.x, height = s.y;}
  FXT_POINT  TopLeft() const {FXT_POINT p; p.x = left; p.y = top; return p;}
  FXT_POINT  TopRight() const {FXT_POINT p; p.x = left + width; p.y = top; return p;}
  FXT_POINT  BottomLeft() const {FXT_POINT p; p.x = left; p.y = top + height; return p;}
  FXT_POINT  BottomRight() const {FXT_POINT p; p.x = left + width; p.y = top + height; return p;}
  void    TopLeft(FXT_POINT tl) {left = tl.x; top = tl.y;}
  void    TopRight(FXT_POINT tr) {width = tr.x - left; top = tr.y;}
  void    BottomLeft(FXT_POINT bl) {left = bl.x; height = bl.y - top;}
  void    BottomRight(FXT_POINT br) {width = br.x - left; height = br.y - top;}
  FXT_POINT  Center() const {FXT_POINT p; p.x = left + width / 2; p.y = top + height / 2; return p;}

  void    GetParallelogram(FXT_PARAL &pg) const {pg.x = left, pg.y = top; pg.x1 = width, pg.y1 = 0; pg.x2 = 0, pg.y2 = height;}

  void    Union(baseType x, baseType y)
  {
    baseType r = right(), b = bottom();
    if (left > x) left = x;
    if (r < x) r = x;
    if (top > y) top = y;
    if (b < y) b = y;
    width = r - left;
    height = b - top;
  }
  void    Union(const FXT_POINT &p) {Union(p.x, p.y);}
  void    Union(const FXT_RECT &rt)
  {
    baseType r = right(), b = bottom();
    if (left > rt.left) left = rt.left;
    if (r < rt.right()) r = rt.right();
    if (top > rt.top) top = rt.top;
    if (b < rt.bottom()) b = rt.bottom();
    width = r - left;
    height = b - top;
  }
  void    Intersect(const FXT_RECT &rt)
  {
    baseType r = right(), b = bottom();
    if (left < rt.left) left = rt.left;
    if (r > rt.right()) r = rt.right();
    if (top < rt.top) top = rt.top;
    if (b > rt.bottom()) b = rt.bottom();
    width = r - left;
    height = b - top;
  }
  FX_BOOL    IntersectWith(const FXT_RECT &rt) const
  {
    FXT_RECT rect = rt;
    rect.Intersect(*this);
    return !rect.IsEmpty();
  }
  FX_BOOL    IntersectWith(const FXT_RECT &rt, FX_FLOAT fEpsilon) const
  {
    FXT_RECT rect = rt;
    rect.Intersect(*this);
    return !rect.IsEmpty(fEpsilon);
  }

  friend  FX_BOOL  operator == (const FXT_RECT &rc1, const FXT_RECT &rc2) {return rc1.left == rc2.left && rc1.top == rc2.top && rc1.width == rc2.width && rc1.height == rc2.height;}
  friend  FX_BOOL  operator != (const FXT_RECT &rc1, const FXT_RECT &rc2) {return rc1.left != rc2.left || rc1.top != rc2.top || rc1.width != rc2.width || rc1.height != rc2.height;}

  baseType left, top;
  baseType width, height;
};

/** @brief Type definition for rectangle class for integer. */
typedef CFX_RTemplate<FX_INT32>         CFX_Rect;
/** @brief Type definition for rectangle class for float. */
typedef CFX_RTemplate<FX_FLOAT>         CFX_RectF;
/** @brief Type definition for pointer to integer rectangle. */
typedef CFX_RTemplate<FX_INT32> *       FX_LPRECT;
/** @brief Type definition for pointer to float rectangle. */
typedef CFX_RTemplate<FX_FLOAT> *    FX_LPRECTF;
/** @brief Type definition for constant pointer to integer rectangle. */
typedef CFX_RTemplate<FX_INT32> const *  FX_LPCRECT;
/** @brief Type definition for constant pointer to float rectangle. */
typedef CFX_RTemplate<FX_FLOAT> const *  FX_LPCRECTF;
/** @brief Type definition for rect array. */
typedef CFX_ArrayTemplate<CFX_RectF>  CFX_RectFArray;

/** The class represents ellipse template. */
template<class baseType>
class CFX_ETemplate : public CFX_RTemplate<baseType>
{
 public:
  typedef CFX_PSVTemplate<baseType>  FXT_POINT;
  typedef CFX_PSVTemplate<baseType>  FXT_SIZE;
  typedef CFX_VTemplate<baseType>    FXT_VECTOR;
  typedef CFX_RTemplate<baseType>    FXT_RECT;

  void    Set(baseType left, baseType top, baseType width, baseType height)  {FXT_RECT::left = left, FXT_RECT::top = top, FXT_RECT::width = width, FXT_RECT::height = height;}
  void    Set(baseType left, baseType top, const FXT_SIZE &size)        {FXT_RECT::left = left, FXT_RECT::top = top, FXT_RECT::Size(size);}
  void    Set(const FXT_POINT &p, baseType width, baseType height)      {FXT_RECT::TopLeft(p), FXT_RECT::width = width, FXT_RECT::height = height;}
  void    Set(const FXT_POINT &p1, const FXT_POINT &p2)            {FXT_RECT::TopLeft(p1), FXT_RECT::width = p2.x - p1.x, FXT_RECT::height = p2.y - p1.y, FXT_RECT::Normalize();}
  void    Set(const FXT_POINT &p, const FXT_VECTOR &v)            {FXT_RECT::TopLeft(p), FXT_RECT::width = v.x, FXT_RECT::height = v.y, FXT_RECT::Normalize();}
  void    SetRadius(const FXT_POINT &p, baseType xRadius, baseType yRadius)  {FXT_RECT::left = p.x - xRadius, FXT_RECT::top = p.y - yRadius, FXT_RECT::width = xRadius * 2, FXT_RECT::height = yRadius * 2;}
  void    Reset()                                {FXT_RECT::left = FXT_RECT::top = FXT_RECT::width = FXT_RECT::height = 0;}

  FX_BOOL    Contains(baseType x, baseType y) const
  {
    x -= FXT_RECT::left + FXT_RECT::width / 2;
    y -= FXT_RECT::top + FXT_RECT::height / 2;
    return ((FX_FLOAT)(x * x) / (FX_FLOAT)(FXT_RECT::width * FXT_RECT::width) + (FX_FLOAT)(y * y) / (FX_FLOAT)(FXT_RECT::height * FXT_RECT::height)) <= 0.25f;
  }
  FX_BOOL    Contains(const FXT_POINT &p) const {return Contains(p.x, p.y);}
  FX_BOOL    Contains(const FXT_RECT &rt) const {return Contains(rt.TopLeft()) && Contains(rt.BottomRight());}

  baseType  XRadius() const {return FXT_RECT::width / 2;}
  baseType  YRadius() const {return FXT_RECT::height / 2;}

  void    GetPointF(FX_FLOAT fRadian, CFX_PointF &point) const
  {
    FX_FLOAT a = (FX_FLOAT)FXT_RECT::width / 2.0f;
    FX_FLOAT b = (FX_FLOAT)FXT_RECT::height / 2.0f;
    FX_FLOAT sinValue = (FX_FLOAT)FXSYS_sin(fRadian);
    FX_FLOAT cosValue = (FX_FLOAT)FXSYS_cos(fRadian);
    FX_FLOAT d = FXSYS_sqrt(b * b * cosValue * cosValue + a * a * sinValue * sinValue);
    fRadian = a * b;
    point.x = fRadian * cosValue / d + FXT_RECT::left + a;
    point.y = fRadian * sinValue / d + FXT_RECT::top + b;
  }
  void    GetPoint(FX_FLOAT fRadian, CFX_Point &point) const
  {
    CFX_PointF p;
    GetPointF(fRadian, p);
    point.x = FXSYS_round(p.x + 0.5f);
    point.y = FXSYS_round(p.y + 0.5f);
  }
};

/** @brief Type definition for ellipse class for integer. */
typedef CFX_ETemplate<FX_INT32> CFX_Ellipse;
/** @brief Type definition for ellipse class for float. */
typedef CFX_ETemplate<FX_FLOAT> CFX_EllipseF;

/** The class represents round corner rectangle. */
template<class baseType>
class CFX_RRTemplate: public CFX_RTemplate<baseType>
{
 public:
  typedef CFX_PSVTemplate<baseType>  FXT_POINT;
  typedef CFX_VTemplate<baseType>    FXT_VECTOR;
  typedef CFX_RTemplate<baseType>    FXT_RECT;
  typedef CFX_RRTemplate<baseType>  FXT_RRECT;

  void  Set(baseType left, baseType top, baseType width, baseType height, baseType xRadius, baseType yRadius) {FXT_RECT::left = left, FXT_RECT::top = top, FXT_RECT::width = width, FXT_RECT::height = height, FXT_RRECT::xRadius = xRadius, FXT_RRECT::yRadius = yRadius;}
  void  Set(const FXT_POINT &p1, const FXT_POINT &p2, baseType xRadius, baseType yRadius) {FXT_RECT::left = p1.x, FXT_RECT::top = p1.y, FXT_RECT::width = p2.x - p1.x, FXT_RECT::height = p2.y - p1.y, FXT_RRECT::xRadius = xRadius, FXT_RRECT::yRadius = yRadius, FXT_RECT::Normalize();}
  void  Set(const FXT_POINT &p, const FXT_VECTOR &v, baseType xRadius, baseType yRadius) {FXT_RECT::TopLeft(p), FXT_RECT::width = v.x, FXT_RECT::height = v.y, FXT_RRECT::xRadius = xRadius, FXT_RRECT::yRadius = yRadius, FXT_RECT::Normalize();}
  void  Set(const FXT_RECT &rt, baseType xRadius, baseType yRadius) {FXT_RECT::left = rt.left, FXT_RECT::top = rt.top, FXT_RECT::width = rt.width, FXT_RECT::height = rt.height, FXT_RRECT::xRadius = xRadius, FXT_RRECT::yRadius = yRadius;}
  void  Reset() {FXSYS_memset32((void*)this, 0, sizeof(FXT_RRECT));}

  /** @brief x radius of round corner. This must not exceed the half width. */
  baseType  xRadius;
  /** @brief y radius of round corner. This must not exceed the half height. */
  baseType  yRadius;
};

/** @brief Type definition for round-corner rectangle class for integer. */
typedef CFX_RRTemplate<FX_INT32> CFX_RoundRect;
/** @brief Type definition for round-corner rectangle class for float. */
typedef CFX_RRTemplate<FX_FLOAT> CFX_RoundRectF;

/** The class for arc template. */
template<class baseType>
class CFX_ATemplate: public CFX_ETemplate<baseType>
{
 public:
  typedef CFX_PSVTemplate<baseType>  FXT_POINT;
  typedef CFX_VTemplate<baseType>    FXT_VECTOR;
  typedef CFX_RTemplate<baseType>    FXT_RECT;
  typedef CFX_ETemplate<baseType>    FXT_ELLIPSE;
  typedef CFX_ATemplate<baseType>    FXT_ARC;

  void    Set(baseType left, baseType top, baseType width, baseType height, FX_FLOAT startAngle, FX_FLOAT sweepAngle) {FXT_RECT::left = left, FXT_RECT::top = top, FXT_RECT::width = width, FXT_RECT::height = height, FXT_ARC::startAngle = startAngle, FXT_ARC::sweepAngle = sweepAngle;}
  void    Set(const FXT_POINT &p1, const FXT_POINT &p2, FX_FLOAT startAngle, FX_FLOAT sweepAngle) {FXT_RECT::left = p1.x, FXT_RECT::top = p1.y, FXT_RECT::width = p2.x - p1.x, FXT_RECT::height = p2.y - p1.y, FXT_ARC::startAngle = startAngle, FXT_ARC::sweepAngle = sweepAngle, FXT_RECT::Normalize();}
  void    Set(const FXT_POINT &p, const FXT_VECTOR &v, FX_FLOAT startAngle, FX_FLOAT sweepAngle) {FXT_RECT::TopLeft(p), FXT_RECT::width = v.x, FXT_RECT::height = v.y, FXT_ARC::startAngle = startAngle, FXT_ARC::sweepAngle = sweepAngle, FXT_RECT::Normalize();}
  void    Set(const FXT_POINT &p, baseType xRadius, baseType yRadius, FX_FLOAT startAngle, FX_FLOAT sweepAngle) {FXT_RECT::left = p.x - xRadius, FXT_RECT::top = p.y - yRadius, FXT_RECT::width = xRadius * 2, FXT_RECT::height = yRadius * 2, FXT_ARC::startAngle = startAngle, FXT_ARC::sweepAngle = sweepAngle;}
  void    Set(const FXT_RECT &rt, FX_FLOAT startAngle, FX_FLOAT sweepAngle) {FXT_RECT::left = rt.left, FXT_RECT::top = rt.top, FXT_RECT::width = rt.width, FXT_RECT::height = rt.height, FXT_ARC::startAngle = startAngle, FXT_ARC::sweepAngle = sweepAngle;}
  void    Set(const FXT_ELLIPSE &ellipse, FX_FLOAT startAngle, FX_FLOAT sweepAngle) {FXT_ELLIPSE::left = ellipse.left, FXT_RECT::top = ellipse.top, FXT_RECT::width = ellipse.width, FXT_RECT::height = ellipse.height, FXT_ARC::startAngle = startAngle, FXT_ARC::sweepAngle = sweepAngle;}
  void    Reset() {FXSYS_memset32((void*)this, 0, sizeof(FXT_ARC));}

  FX_FLOAT  EndAngle() const            {return startAngle + sweepAngle;}
  void    EndAngle(FX_FLOAT endAngle)       {sweepAngle = endAngle - startAngle;}
  void    StartPointF(CFX_PointF &point) const  {FXT_ELLIPSE::GetPointF(startAngle, point);}
  void    EndPointF(CFX_PointF &point) const    {FXT_ELLIPSE::GetPointF(EndAngle(), point);}
  void    StartPoint(CFX_Point &point) const    {FXT_ELLIPSE::GetPoint(startAngle, point);}
  void    EndPoint(CFX_Point &point) const    {FXT_ELLIPSE::GetPoint(EndAngle(), point);}

    /** @brief Start angle to draw arc. Positive is counterclockwise, in radian. */
  FX_FLOAT  startAngle;
    /** @brief Sweep angle to draw arc. Positive is counterclockwise from starting angle, in radian. */
  FX_FLOAT  sweepAngle;
};

/** @brief Type definition for arc class for integer. */
typedef CFX_ATemplate<FX_INT32> CFX_Arc;
/** @brief Type definition for arc class for float. */
typedef CFX_ATemplate<FX_FLOAT> CFX_ArcF;
//<<<+++OPENSOURCE_END

/** 
 * The struct represents integer rectangle for Windows coordinates.
 * Defined as equivalent of Windows RECT structure, with some convenient function members.
 * This structure use Windows space where Y axis runs from top to bottom.
 */
struct FX_RECT
{
  /** @brief The left */
  int      left;
  /** @brief The top */
  int      top;
  /** @brief The right */
  int      right;
  /** @brief The bottom */
  int      bottom;

  /**
   * @brief Construct a rect not initialized.
   */
  FX_RECT() {
  left = 0;
  top = 0;
  right = 0;
  bottom = 0;
  }

  /**
   * @brief Construct a rect with left-top and right bottom corners.
   *
   * @param[in] left1    The left.
   * @param[in] top1     The top.
   * @param[in] right1   The right.
   * @param[in] bottom1  The bottom.
   */
  FX_RECT(int left1, int top1, int right1, int bottom1)
  { left = left1; top = top1; right = right1; bottom = bottom1; }

  /**
   * @brief Get the width of the rect.
   *
   * @return The width of the rect.
   */
  int      Width() const { return right - left; }

  /**
   * @brief Get the height of the rect.
   *
   * @return The height of the rect.
   */
  int      Height() const { return bottom - top; }

  /**
   * @brief Verify whether the rect is empty.
   *
   * @return <b>true</b> means current rect is empty, while <b>false</b> means not.
   */
  FX_BOOL    IsEmpty() const { return right <= left || bottom <= top; }

  /**
   * @brief Normalize the rect. Make sure left <= right, top <= bottom.
   *
   * @return None.
   */
  void    Normalize();

  /**
   * @brief Intersect with a rect.
   *
   * @param[in] src  The rect to intersect with.
   *
   * @return None.
   */
  void    Intersect(const FX_RECT& src);

  /**
   * @brief Intersect with a rect.
   *
   * @param[in] left1    The left of the rect to intersect with.
   * @param[in] top1     The top of the rect to intersect with.
   * @param[in] right1   The right of the rect to intersect with.
   * @param[in] bottom1  The bottom of the rect to intersect with.
   *
   * @return None.
   */
  void    Intersect(int left1, int top1, int right1, int bottom1) { Intersect(FX_RECT(left1, top1, right1, bottom1)); }

  /**
   * @brief Union with a rect.
   *
   * @param[in] other_rect  The rect to union with.
   *
   * @return None.
   */
  void    Union(const FX_RECT& other_rect);

  /**
   * @brief Compare(==) operator overload. Compare two rectangles. Please make sure they are normalized first.
   *
   * @param[in] src  The rect to compare.
   *
   * @return <b>true</b> means equal, while <b>false</b> means not equal.
   */
  FX_BOOL    operator == (const FX_RECT& src) const
  { return left == src.left && right == src.right && top == src.top && bottom == src.bottom; }

  /**
   * @brief Compare(!=) operator overload. Compare two rectangles. Please make sure they are normalized first.
   *
   * @param[in] src  The rect to compare.
   *
   * @return <b>true</b> means not equal, while <b>false</b> means equal.
   */
  FX_BOOL    operator != (const FX_RECT& src) const
  { return left != src.left || right != src.right || top != src.top || bottom != src.bottom; }

  /**
   * @brief Shift the coordinates by delta value of x and y directions.
   *
   * @param[in] dx  The delta value of x-direction.
   * @param[in] dy  The delta value of y-direction.
   *
   * @return None.
   */
  void    Offset(int dx, int dy) { left += dx; right += dx; top += dy; bottom += dy; }

  /**
   * @brief Check if current rectangle fully contains the other provided rectangle.
   *        That means to check if the other rectangle is fully inside current one.
   *
   * @param[in] other_rect  The other provided rect.
   *
   * @return <b>true</b> means current rect fully contains the other rectangle, while <b>false</b> means not.
   */
  FX_BOOL    Contains(const FX_RECT& other_rect) const
  {
    // Assume both rects are normalized!
    return other_rect.left >= left && other_rect.right <= right && other_rect.top >= top && other_rect.bottom <= bottom;
  }

  /**
   * @brief Check if current rectangle contains the provided point.
   *        That means to check if the provided point is inside current one.
   *
   * @param[in] x  The x coordinate of the provided point.
   * @param[in] y  The y coordinate of the provided point.
   *
   * @return <b>true</b> means current rect contains the provided point, while <b>false</b> means not.
   */
  FX_BOOL    Contains(int x, int y) const
  {
    // Assume the rectangle is normalized!
    return x >= left && x < right && y >= top && y < bottom;
  }
  /**
   * @brief Check if current rectangle is valid.
   *
   * @return <b>true</b> means valid, while <b>false</b> means invalid.
   */
  FX_BOOL    Valid() const;
};

/**
 * The struct for small rectangle. This uses short types for coordinates in comparing with RECT.
 */
struct FX_SMALL_RECT
{
  /** @brief The left */
  FX_SHORT  Left;
  /** @brief The top */
  FX_SHORT  Top;
  /** @brief The right */
  FX_SHORT  Right;
  /** @brief The bottom */
  FX_SHORT  Bottom;
};

/**
 * A float-point coordination rectangle.
 * A normalized float-point rectangle always has top larger than bottom, which is the opposite of Windows rectangle.
 */
class CFX_FloatRect : public CFX_Object
{
 public:
  /**
   * @brief Construct an empty rectangle.
   */
  CFX_FloatRect() { left = right = bottom = top = 0; }

  /**
   * @brief Construct a rectangle with left-bottom and right-top corners.
   *
   * @param[in] left1    The x-coordinate of the input left-bottom corner.
   * @param[in] bottom1  The y-coordinate of the input left-bottom corner.
   * @param[in] right1   The x-coordinate of the input right-top corner.
   * @param[in] top1     The y-coordinate of the input right-top corner.
   */
  CFX_FloatRect(FX_FLOAT left1, FX_FLOAT bottom1, FX_FLOAT right1, FX_FLOAT top1)
  { left = left1; bottom = bottom1; right = right1; top = top1; }
  /**
   * @brief Construct a rectangle with an array of left, bottom, right, top values.
   *
   * @param[in] pArray  The input array.
   */
  CFX_FloatRect(const FX_FLOAT* pArray)
  { left = pArray[0]; bottom = pArray[1]; right = pArray[2]; top = pArray[3]; }
  /**
   * @brief Construct a rectangle with a FX_RECT object.
   *
   * @param[in] rect  The input FX_RECT object.
   */
  CFX_FloatRect(const FX_RECT& rect);

  /**
   * @brief Verify whether the rect is empty.
   *
   * @return <b>true</b> meanas current rect is empty, while <b>false</b> means not.
   */
  FX_BOOL        IsEmpty() const { return left >= right || bottom >= top; }

  /**
   * @brief Normalize the rect. Make sure left <= right, and bottom <= top.
   *
   * @return None.
   */
  void        Normalize();

  /**
   * @brief Compare(==) operator overload. Compare two rectangles. Please make sure they are normalized first.
   *
   * @param[in] src  The rect to compare.
   *
   * @return <b>true</b> means equal, while <b>false</b> means not equal.
   */
  FX_BOOL    operator == (const CFX_FloatRect& src) const
  { return FXSYS_fabs(left - src.left) < FLT_EPSILON && FXSYS_fabs(right - src.right) < FLT_EPSILON &&
    FXSYS_fabs(top - src.top) < FLT_EPSILON && FXSYS_fabs(bottom - src.bottom) < FLT_EPSILON; }

  /**
   * @brief Compare(!=) operator overload. Compare two rectangles. Please make sure they are normalized first.
   *
   * @param[in] src  The rect to compare.
   *
   * @return <b>true</b> means not equal, while <b>false</b> means equal.
   */
  FX_BOOL    operator != (const CFX_FloatRect& src) const
    { return FXSYS_fabs(left - src.left) > FLT_EPSILON || FXSYS_fabs(right - src.right) > FLT_EPSILON ||
    FXSYS_fabs(top - src.top) > FLT_EPSILON || FXSYS_fabs(bottom - src.bottom) > FLT_EPSILON; }

  /**
   * @brief Reset rectangle, set coordinates to 0. 
   * 
   *  @return None.
   */
  void        Reset() {left = right = bottom = top = 0;}

  /**
   * @brief Check if current rectangle fully contains the other provided rectangle.
   *        That means to check if the other rectangle is fully inside current one.
   *
   * @param[in] other_rect  The other provided rect.
   *
   * @return <b>true</b> means current rectangle fully contains the other one, while <b>false</b> means not.
   */
  FX_BOOL        Contains(const CFX_FloatRect& other_rect) const;

  /**
   * @brief Check if current rectangle fully contains the provided point.
   *        That means to check if the provided point is inside current rectangle.
   *
   * @param[in] x  The x coordinate of the provided point.
   * @param[in] y  The y coordinate of the provided point.
   *
   * @return <b>true</b> means current rectangle contains the provided point, while <b>false</b> means not.
   */
  FX_BOOL        Contains(FX_FLOAT x, FX_FLOAT y) const;

  /**
   * @brief Transform a rectangle. The result rectangle is always normalized.
   *
   * @param[in] pMatrix  The transformation matrix.
   *
   * @return None.
   */
  void        Transform(const CFX_Matrix* pMatrix);

  /**
   * @brief Intersect with a rect.
   *
   * @param[in] other_rect  The rect to intersect with.
   *
   * @return None.
   */
  void        Intersect(const CFX_FloatRect& other_rect);

  /**
   * @brief Union with a rect.
   *
   * @param[in] other_rect  The rect to union with.
   *
   * @return None.
   */
  void        Union(const CFX_FloatRect& other_rect);

  /** 
   * @brief Convert to an inner integer rectangle. 
   *
   * @return The inner integer rectangle.
   */
  FX_RECT        GetInnerRect() const;

  /** 
   * @brief Convert to an outer integer rectangle.
   *
   * @return The outer integer rectangle.
   */
  FX_RECT        GetOutterRect() const;

  /** 
   * @brief Get a closest integer rectangle.
   *
   * @return The closest integer rectangle.
   */
  FX_RECT        GetClosestRect() const;
  /**
   * @brief Subtract a rectangle area from this rectangle. The result might be up to 4 rectangles.
   *        The number of result rectangles are returned. Caller must prepare enough rectangles (up to 4).
   *
   * @param[in] substract_rect  The rectangle to be subtracted.
   * @param[out] pRects         The rectangle array to receive result rectangles.
   *
   * @return The number of result rectangles.
   */
  int          Substract4(CFX_FloatRect& substract_rect, CFX_FloatRect* pRects);
  /**
   * @brief Initialize the rectangle to a single point.
   *
   * @param[in] x  The x-coordinate of the input point.
   * @param[in] y  The y-coordinate of the input point.
   *
   * @return None.
   */
  void        InitRect(FX_FLOAT x, FX_FLOAT y) { left = right = x; bottom = top = y; }

  /**
   * @brief Update the rectangle to contain the specified point.
   *
   * @param[in] x  The x-coordinate of the input point.
   * @param[in] y  The y-coordinate of the input point.
   *
   * @return None.
   */
  void        UpdateRect(FX_FLOAT x, FX_FLOAT y);

  /**
   * @brief Get the width of the rectangle.
   *
   * @return Width of the rectangle.
   */
  FX_FLOAT      Width() const { return right - left; }

  /**
   * @brief Get the height of the rectangle.
   *
   * @return Height of the rectangle.
   */
  FX_FLOAT      Height() const { return top - bottom; }

  /**
   * @brief Increases the width and height of the rectangle.
   *
   * @param[in] x  The number to inflate the left and right of the rectangle.
   * @param[in] y  The number to inflate the top and bottom of the rectangle.
   *
   * @return None.
   */
  void        Inflate(FX_FLOAT x, FX_FLOAT y) { Inflate(x, y, x, y); }
  /**
   * @brief Increases the width and height of the rectangle.
   *
   * @param[in] left    The number to inflate the left of the rectangle.
   * @param[in] bottom  The number to inflate the bottom of the rectangle.
   * @param[in] right   The number to inflate the right of the rectangle.
   * @param[in] top     The number to inflate the top of the rectangle.
   *
   * @return None.
   */
  void        Inflate(FX_FLOAT left, FX_FLOAT bottom, FX_FLOAT right, FX_FLOAT top) {Normalize(); this->left -= left; this->bottom -= bottom; this->right += right; this->top += top;}
  
  /**
   * @brief Increases the width and height of the rectangle.
   *
   * @param[in] rt  The rectangle to inflate each side.
   *
   * @return None.
 */
  void        Inflate(const CFX_FloatRect &rt) {Inflate(rt.left, rt.bottom, rt.right, rt.top);}

  /**
   * @brief Decreases the width and height of the rectangle.
   *
   * @param[in] x  The number to deflate the left and right of the rectangle.
   * @param[in] y  The number to deflate the top and bottom of the rectangle.
   *
   * @return None.
   */
  void        Deflate(FX_FLOAT x, FX_FLOAT y) { Deflate(x, y, x, y); }
  /**
   * @brief Decreases the width and height of the rectangle.
   *
   * @param[in] left    The number to deflate the left of the rectangle.
   * @param[in] bottom  The number to deflate the bottom of the rectangle.
   * @param[in] right   The number to deflate the right of the rectangle.
   * @param[in] top     The number to deflate the top of the rectangle.
   *
   * @return None.
   */
  void        Deflate(FX_FLOAT left, FX_FLOAT bottom, FX_FLOAT right, FX_FLOAT top) { Inflate(-left, -bottom, -right, -top); }
  /**
   * @brief Decreases the width and height of the rectangle.
   *
   * @param[in] rt  The rectangle to deflate each side.
   *
   * @return None.
   */
  void        Deflate(const CFX_FloatRect &rt) {Deflate(rt.left, rt.bottom, rt.right, rt.top);}

  /**
   * @brief Translate rectangle.
   *
   * @param[in] e  Offset in X-axis.
   * @param[in] f  Offset in Y-axis.
   *
   * @return None.
   */
  void        Translate(FX_FLOAT e, FX_FLOAT f) {left += e; right += e; top += f; bottom += f;}

  /**
   * @brief Get the bounding box of input points array.
   *
   * @param[in] pPoints  The input points array.
   * @param[in] nPoints  The number of points in the array.
   *
   * @return A floating-point coordination rectangle.
   */
  static CFX_FloatRect  GetBBox(const CFX_FloatPoint* pPoints, int nPoints);

  /** @brief The left. */
  FX_FLOAT      left;
  /** @brief The right. */
  FX_FLOAT      right;
  /** @brief The bottom. */
  FX_FLOAT      bottom;
  /** @brief The top. */
  FX_FLOAT      top;
};

/**
 * @brief Check if a rectangle is adjacent to the other rectangle in the horizontal or vertical direction.
 *
 * @param[in] rect1               A rectangle which is to be check if adjacent to parameter <i>rect2</i>.
 * @param[in] rect2               The other rectangle.
 * @param[in] alignmentTolerance  Alignment tolerance to be allowed between two rectangles. Measured in coordinate units, and should be non-negative value.
 * @param[in] distanceTolerance   Distance tolerance to be allowed between two rectangles. Measured in coordinate units, and should be non-negative value.
 * @param[in] direction           Specify a direction to judge adjacent state between two rectangles:
 *                                <ul>
 *                                <li>0 means horizontal direction.</li>
 *                                <li>1 means vertical direction.</li>
 *                                </ul>
 *
 * @return <b>true</b> means the specified rectangle is adjacent to the other specified rectangle in specified direction,
 *         while <b>false</b> means the specified rectangle is not adjacent to the other specified rectangle in specified direction.
 */
FX_BOOL	FX_IsRectAdjacent(const CFX_FloatRect& rect1, const CFX_FloatRect& rect2, FX_FLOAT alignmentTolerance, FX_FLOAT distanceTolerance, int direction);

/** @brief Rectangle array. */
typedef  CFX_ArrayTemplate<CFX_FloatRect> CFX_RectArray;

/**
 * Affine (linear) transformation matrix.
 *
 * It defines six coefficients: a, b, c, d, e, f.
 * The transformation equations are:
 * dest_x = a * src_x + c * src_y + e;
 * dest_y = b * src_x + d * src_y + f;
 */
class CFX_Matrix : public CFX_Object
{
 public:
  /** 
   * @brief Construct a identity transformation matrix. 
   */
  CFX_Matrix() {a = d = 1; b = c = e = f = 0;}

  /**
   * @brief Construct a matrix with six input coefficients.
   *
   * @param[in] a1  The input coefficient a.
   * @param[in] b1  The input coefficient b.
   * @param[in] c1  The input coefficient c.
   * @param[in] d1  The input coefficient d.
   * @param[in] e1  The input coefficient e.
   * @param[in] f1  The input coefficient f.
   */
  CFX_Matrix(FX_FLOAT a1, FX_FLOAT b1, FX_FLOAT c1, FX_FLOAT d1, FX_FLOAT e1, FX_FLOAT f1)
  {a = a1; b = b1; c = c1; d = d1; e = e1; f = f1;}

    /**
   * @brief Compare(==) operator overload. Compare two matrixs.
   *
   * @param[in] src  The matrix to compare.
   *
   * @return <b>true</b> means equal, while <b>false</b> means not equal.
   */
  FX_BOOL    operator == (const CFX_Matrix& src) const
  { return FXSYS_fabs(a - src.a) < FLT_EPSILON && FXSYS_fabs(b - src.b) < FLT_EPSILON &&
    FXSYS_fabs(c - src.c) < FLT_EPSILON && FXSYS_fabs(d - src.d) < FLT_EPSILON &&
    FXSYS_fabs(e - src.e) < FLT_EPSILON && FXSYS_fabs(f - src.f) < FLT_EPSILON; }

  /**
   * @brief Compare(!=) operator overload. Compare two matrixs.
   *
   * @param[in] src      The matrix to compare.
   *
   * @return <b>true</b> means not equal, while <b>false</b> means equal.
   */
  FX_BOOL    operator != (const CFX_Matrix& src) const
  { return FXSYS_fabs(a - src.a) > FLT_EPSILON || FXSYS_fabs(b - src.b) > FLT_EPSILON ||
    FXSYS_fabs(c - src.c) > FLT_EPSILON || FXSYS_fabs(d - src.d) > FLT_EPSILON ||
    FXSYS_fabs(e - src.e) > FLT_EPSILON || FXSYS_fabs(f - src.f) > FLT_EPSILON; }

  /**
   * @brief Change the coefficients in the matrix.
   *
   * @param[in] a  The input coefficient a.
   * @param[in] b  The input coefficient b.
   * @param[in] c  The input coefficient c.
   * @param[in] d  The input coefficient d.
   * @param[in] e  The input coefficient e.
   * @param[in] f  The input coefficient f.
   *
   * @return None.
   */
  void      Set(FX_FLOAT a, FX_FLOAT b, FX_FLOAT c, FX_FLOAT d, FX_FLOAT e, FX_FLOAT f);

  /**
   * @brief Change the coefficients in the matrix.
   *
   * @param[in] n The input coefficient array.
   *
   * @return None.
   */
  void      Set(const FX_FLOAT n[6]);

  /** 
   * @brief Set the matrix to be an identity transformation matrix. 
   *
   * @return None.
   */
  void      SetIdentity() {a = d = 1; b = c = e = f = 0;}

  /**
   * @brief Set the coefficients of the inverse of another matrix to this matrix.
   *
   * @param[in] m  The input matrix.
   *
   * @return None.
   */
  void      SetReverse(const CFX_Matrix &m);

  /**
   * @brief Concatenate with another matrix.
   *
   * @param[in] a           The coefficient a of the input matrix.
   * @param[in] b           The coefficient b of the input matrix.
   * @param[in] c           The coefficient c of the input matrix.
   * @param[in] d           The coefficient d of the input matrix.
   * @param[in] e           The coefficient e of the input matrix.
   * @param[in] f           The coefficient f of the input matrix.
   * @param[in] bPrepended  If this is <b>true</b>, the concatenation matrix is multiplied at left side, or at right side.  
   *
   * @return None.
   */
  void      Concat(FX_FLOAT a, FX_FLOAT b, FX_FLOAT c, FX_FLOAT d, FX_FLOAT e, FX_FLOAT f, FX_BOOL bPrepended = false);
  /**
   * @brief Concatenate with another matrix.
   *
   * @param[in] m           The input matrix.
   * @param[in] bPrepended  If this is <b>true</b>, the concatenation matrix is multiplied at left side, or at right side.
   *
   * @return None.
   */
  void      Concat(const CFX_Matrix &m, FX_BOOL bPrepended = false);
  /**
   * @brief Concatenate the inverse of another matrix.
   *
   * @param[in] m           The input matrix.
   * @param[in] bPrepended  If this is <b>true</b>, the concatenation matrix is multiplied at left side, or at right side.
   *
   * @return None.
   */
  void      ConcatInverse(const CFX_Matrix& m, FX_BOOL bPrepended = false);
  /**
   * @brief Reset current matrix.
   *
   * @return None.
   */
  void      Reset() {SetIdentity();}

  /**
   * @brief Copy coefficients from another matrix.
   *
   * @param[in] m  The input matrix.
   *
   * @return None.
   */
  void      Copy(const CFX_Matrix& m) {*this = m;}

  /**
   * @brief Determine whether a matrix is an identity transformation or not.
   *
   * @return <b>true</b> means current matrix is identity, while <b>false</b> means not.
   */
  FX_BOOL      IsIdentity() const {return a == 1 && b == 0 && c == 0 && d == 1 && e == 0 && f == 0;}

  /**
   * @brief Determine whether a matrix is invertible or not.
   *
   * @return <b>true</b> means current matrix is invertible, while <b>false</b> means not.
   */
  FX_BOOL      IsInvertible() const;

  /**
   * @brief Whether this matrix has rotating of 90, or -90 degrees.
   *
   * @return <b>true</b> means current matrix has rotating of 90, or -90 degrees, while <b>false</b> means not.
   */
  FX_BOOL      Is90Rotated() const;

  /**
   * @brief Whether this matrix has scaling (or translating) only. No rotating.
   *
   * @return <b>true</b> means current matrix has scaling (or translating) only, while <b>false</b> means not.
   */
  FX_BOOL      IsScaled() const;

  /**
   * @brief Translate the matrix.
   *
   * @param[in] x           The x-direction delta value.
   * @param[in] y           The y-direction delta value.
   * @param[in] bPrepended  If this is <b>true</b>, a translation matrix is multiplied at left side, or at right side.
   *
   * @return None.
   */
  void      Translate(FX_FLOAT x, FX_FLOAT y, FX_BOOL bPrepended = false);
  /**
   * @brief Translate the matrix. using integer value.
   *
   * @param[in] x           The x-direction delta integer value.
   * @param[in] y           The y-direction delta integer value.
   * @param[in] bPrepended  If this is <b>true</b>, a translation matrix is multiplied at left side, or at right side.
   *
   * @return None.
   */
  void      TranslateI(FX_INT32 x, FX_INT32 y, FX_BOOL bPrepended = false) {Translate((FX_FLOAT)x, (FX_FLOAT)y, bPrepended);}
  /**
   * @brief Scale the matrix.
   *
   * @param[in] sx          The x-direction scale coefficient.
   * @param[in] sy          The y-direction scale coefficient.
   * @param[in] bPrepended  If this is <b>true</b>, a scaling matrix is multiplied at left side, or at right side.
   *
   * @return None.
   */
  void      Scale(FX_FLOAT sx, FX_FLOAT sy, FX_BOOL bPrepended = false);
  /**
   * @brief Rotate the matrix.
   *
   * @param[in] fRadian     Rotation angle in radian.
   * @param[in] bPrepended  If it's true, a rotation matrix is multiplied at left side, or at right side.
   *
   * @return None.
   */
  void      Rotate(FX_FLOAT fRadian, FX_BOOL bPrepended = false);
  /**
   * @brief Rotate the matrix at a position.
   *
   * @param[in] fRadian     Rotation angle in radian.
   * @param[in] x           The x coordinate from which to rotate.
   * @param[in] y           The y coordinate from which to rotate.
   * @param[in] bPrepended  If this is <b>true</b>, a rotation matrix is multiplied at left side, or at right side.
   *
   * @return None.
   */
  void      RotateAt(FX_FLOAT fRadian, FX_FLOAT x, FX_FLOAT y, FX_BOOL bPrepended = false);
  /**
   * @brief Shear the matrix.
   *
   * @param[in] fAlphaRadian  Shearing angle of x axis.
   * @param[in] fBetaRadian   Shearing angle of y axis.
   * @param[in] bPrepended    If this is <b>true</b>, a shearing matrix is multiplied at left side, or at right side.
   *
   * @return None.
   */
  void      Shear(FX_FLOAT fAlphaRadian, FX_FLOAT fBetaRadian, FX_BOOL bPrepended = false);

  /**
   * @brief Get a matrix that transforms a source rectangle to dest rectangle.
   *
   * @param[in] dest  The dest rectangle.
   * @param[in] src   The source rectangle.
   *
   * @return None.
   */
  void      MatchRect(const CFX_FloatRect &dest, const CFX_FloatRect &src);

  /** 
   * @brief Get the x-direction unit size.
   *
   * @return The x-direction unit size.
   */
  FX_FLOAT    GetXUnit() const;
  
  /** 
   * @brief Get the y-direction unit size.
   *
   * @return The y-direction unit size.
   */
  FX_FLOAT    GetYUnit() const;

  /**
   * @brief Get a parallelogram conposing two unit vectors.
   *
   * @param[out] pg  It recieves the outputting unit parallelogram.
   *
   * @return None.
   */
  void      GetUnitParallelogram(CFX_ParallelogramF &pg) const;
  /**
   * @brief Get a bounding rectangle of the parallelogram composing two unit vectors.
   *
   * @param[out] rect  It recieves the outputting unit rect.
   *
   * @return None.
   */
  void      GetUnitRect(CFX_RectF &rect) const;
  /**
   * @brief Get a bounding rectangle of the parallelogram composing two unit vectors.
   * 
   * @return The unit rect.
   */
  CFX_FloatRect  GetUnitRect() const;
  /** 
   * @brief Get area of the parallelogram composing two unit vectors. 
   *
   * @return The area of the parallelogram composing two unit vectors. 
   */
  FX_FLOAT    GetUnitArea() const;

#ifdef _FXGE_IMAGERENDER_SHORTCUT_
  const FX_INT32  GetRotation()  const;
  const FX_BOOL  NeedTransform() const;
#endif

  /**
   * @brief Transform a x-distance.
   *
   * @param[in] dx  The input x-distance.
   *
   * @return The transformed distance.
   */
  FX_FLOAT    TransformXDistance(FX_FLOAT dx) const;
  /**
   * @brief Transform a x-distance.
   *
   * @param[in] dx  The input x-distance.
   *
   * @return The transformed distance.
   */
  FX_INT32    TransformXDistance(FX_INT32 dx) const;
  /**
   * @brief Transform a y-distance.
   *
   * @param[in] dy  The input y-distance.
   *
   * @return The transformed distance.
   */
  FX_FLOAT    TransformYDistance(FX_FLOAT dy) const;
  /**
   * @brief Transform a y-distance.
   *
   * @param[in] dy  The input y-distance.
   *
   * @return The transformed distance.
   */
  FX_INT32    TransformYDistance(FX_INT32 dy) const;
  /**
   * @brief Transform distance specified by x and y value.
   *
   * @param[in] dx  The input x value.
   * @param[in] dy  The input y value.
   *
   * @return The transformed distance.
   */
  FX_FLOAT    TransformDistance(FX_FLOAT dx, FX_FLOAT dy) const;
  /**
   * @brief Transform distance specified by x and y value.
   *
   * @param[in] dx  The input x value.
   * @param[in] dy  The input y value.
   *
   * @return The transformed distance.
   */
  FX_INT32    TransformDistance(FX_INT32 dx, FX_INT32 dy) const;
  /**
   * @brief Transform a distance.
   *
   * @param[in] distance  The input distance.
   *
   * @return The transformed distance.
   */
  FX_FLOAT    TransformDistance(FX_FLOAT distance) const;

  /**
   * @brief Transform point specified by x and y value.
   *
   * @param[in,out] x  The input x-coordinate of the point, and it receives the output transformed x-coordinate.
   * @param[in,out] y  The input y-coordinate of the point, and it receives the output transformed y-coordinate.
   *
   * @return None.
   */
  void      TransformPoint(FX_FLOAT &x, FX_FLOAT &y) const;
  /**
   * @brief Transform point specified by x and y value.
   *
   * @param[in,out] x  The input x-coordinate of the point, and it receives the output transformed x-coordinate.
   * @param[in,out] y  The input y-coordinate of the point, and it receives the output transformed y-coordinate.
   *
   * @return None.
   */
  void      TransformPoint(FX_INT32 &x, FX_INT32 &y) const;
  /**
   * @brief Transform points.
   *
   * @param[in,out] points  The input a array of the points, and it receives the output array of the transformed points.
   * @param[in]     iCount  The input count of the points.
   *
   * @return None.
   */
  void      TransformPoints(CFX_PointF *points, FX_INT32 iCount) const;

  /**
   * @brief Transform points.
   *
   * @param[in,out] points  The input a array of the points, and it receives the output array of the transformed points.
   * @param[in]     iCount  The input count of the points.
   *
   * @return None.
   */
  void      TransformPoints(CFX_Point *points, FX_INT32 iCount) const;

  /**
   * @brief Transform a point.
   *
   * @param[in,out] x  The input x-coordinate of the point, and It receives the output transformed x-coordinate.
   * @param[in,out] y  The input y-coordinate of the point, and It receives the output transformed y-coordinate.
   *
   * @return None.
   */
  void      Transform(FX_FLOAT& x, FX_FLOAT& y) const {TransformPoint(x, y);}

  /**
   * @brief Transform a point.
   *
   * @param[in] x    The input x-coordinate of the point.
   * @param[in] y    The input y-coordinate of the point.
   * @param[out] x1  It receives the output transformed x-coordinate.
   * @param[out] y1  It receives the output transformed y-coordinate.
   *
   * @return None.
   */
  void      Transform(FX_FLOAT x, FX_FLOAT y, FX_FLOAT& x1, FX_FLOAT& y1) const {x1 = x, y1 = y; TransformPoint(x1, y1);}

  /**
   * @brief Transform a vector.
   *
   * @param[in,out] v  The input vector, and it receives the output transformed vector.
   *
   * @return None.
   */
  void      TransformVector(CFX_VectorF &v) const;

  /**
   * @brief Transform a vector.
   *
   * @param[in,out] v  The input vector, and it receives the output transformed vector.
   *
   * @return None.
   */
  void      TransformVector(CFX_Vector &v) const;

  /**
   * @brief Transform a parallelogram.
   *
   * @param[in,out] pg  The input parallelogram, and it receives the output transformed parallelogram.
   *
   * @return None.
   */
  void      TransformParallelogram(CFX_ParallelogramF &pg) const;

  /**
   * @brief Transform a parallelogram.
   *
   * @param[in,out] pg  The input parallelogram, and it receives the output transformed parallelogram.
   *
   * @return None.
   */
  void      TransformParallelogram(CFX_Parallelogram &pg) const;

  /**
   * @brief Transform a rectangle and return a bounding rectangle.
   *        The result rectangle is always normalized: left <= right, and top <= bottom.
   *
   * @param[in,out] rect  The input rectangle, and it receives the output transformed rectangle.
   *
   * @return None.
   */
  void      TransformRect(CFX_RectF &rect) const;

  /**
   * @brief Transform a rectangle and return a bounding rectangle.
   *        The result rectangle is always normalized: left <= right, and top <= bottom.
   *
   * @param[in,out] rect  The input rectangle, and it receives the output transformed rectangle.
   *
   * @return None.
   */
  void      TransformRect(CFX_Rect &rect) const;

  /**
   * @brief Transform a rectangle and return a bounding rectangle.
   *        The result rectangle is always normalized: left <= right, and bottom <= top.
   *
   * @param[in,out] left    The input x-coordinate of the left-bottom corner, and it receives the output transformed and normalized x-coordinate.
   * @param[in,out] right   The input x-coordinate of the right-top corner, and it receives the output transformed and normalized x-coordinate.
   * @param[in,out] top     The input y-coordinate of the right-top corner, and it receives the output transformed and normalized y-coordinate.
   * @param[in,out] bottom  The input y-coordinate of the left-bottom corner, and it receives the output transformed and normalized y-coordinate.
   *
   * @return None.
   */
  void      TransformRect(FX_FLOAT& left, FX_FLOAT& right, FX_FLOAT& top, FX_FLOAT& bottom) const;

  /**
   * @brief Transform a rectangle and return a bounding rectangle.
   *        The result rectangle is always normalized: left <= right, and bottom <= top.
   *
   * @param[in,out] rect  The input rectangle, and it receives the output transformed and normalized rectangle.
   *
   * @return None.
   */
  void      TransformRect(CFX_FloatRect& rect) const {TransformRect(rect.left, rect.right, rect.top, rect.bottom);}
  /**
   * @brief Transform a rectangle and return a bounding rectangle.
   *        The result rectangle is always normalized: left <= right, and bottom <= top.
   *
   * @param[in,out] rect  The input rectangle, and it receives the output transformed and normalized rectangle.
   *
   * @return None.
   */
  void      TransformRect(FX_RECT& rect) const;

  /**
   * @brief Transform a round rectangle.
   *
   * @param[in,out] rr  The input round rectangle, and it receives the output transformed round rectangle.
   *
   * @return None.
   */
  void      TransformRoundRect(CFX_RoundRectF &rr) const;

  /**
   * @brief Transform a round rectangle.
   *
   * @param[in,out] rr  The input round rectangle, and it receives the output transformed round rectangle.
   *
   * @return None.
   */
  void      TransformRoundRect(CFX_RoundRect &rr) const;

  /**
   * @brief Get the coefficient a.
   *
   * @return The coefficient a.
   */
  FX_FLOAT    GetA() const {return a;}

  /**
   * @brief Get the coefficient b.
   *
   * @return The coefficient b.
   */
  FX_FLOAT    GetB() const {return b;}
  
  /**
   * @brief Get the coefficient c.
   *
   * @return The coefficient c.
   */
  FX_FLOAT    GetC() const {return c;}

  /**
   * @brief Get the coefficient d.
   *
   * @return The coefficient d.
   */
  FX_FLOAT    GetD() const {return d;}

  /**
   * @brief Get the coefficient e.
   *
   * @return The coefficient e.
   */
  FX_FLOAT    GetE() const {return e;}

  /**
   * @brief Get the coefficient f.
   *
   * @return The coefficient f.
   */
  FX_FLOAT    GetF() const {return f;}

 public:
  /** @brief The coefficient a.*/
  FX_FLOAT a;
  /** @brief The coefficient b.*/
  FX_FLOAT b;
  /** @brief The coefficient c.*/
  FX_FLOAT c;
  /** @brief The coefficient d.*/
  FX_FLOAT d;
  /** @brief The coefficient e.*/
  FX_FLOAT e;
  /** @brief The coefficient f.*/
  FX_FLOAT f;
};

class CFX_Vector_3by1 : public CFX_Object
{
 public:
CFX_Vector_3by1():
  a(0.0f),
  b(0.0f),
  c(0.0f)
  {}
  CFX_Vector_3by1(FX_FLOAT a1, FX_FLOAT b1, FX_FLOAT c1):
    a(a1),
    b(b1),
    c(c1)
  {}
  FX_FLOAT a;
  FX_FLOAT b;
  FX_FLOAT c;
};

class CFX_Matrix_3by3 : public CFX_Object
{
 public:
CFX_Matrix_3by3():a(0.0f), b(0.0f), c(0.0f), d(0.0f), e(0.0f), f(0.0f), g(0.0f), h(0.0f), i(0.0f)
  {}

  CFX_Matrix_3by3(FX_FLOAT a1, FX_FLOAT b1, FX_FLOAT c1, FX_FLOAT d1, FX_FLOAT e1, FX_FLOAT f1, FX_FLOAT g1, FX_FLOAT h1, FX_FLOAT i1) :
    a(a1), b(b1), c(c1), d(d1), e(e1), f(f1), g(g1), h(h1), i(i1)
  {}
  CFX_Matrix_3by3 Inverse();
  CFX_Matrix_3by3 Multiply(const CFX_Matrix_3by3 &m);
  CFX_Vector_3by1 TransformVector(const CFX_Vector_3by1 &v) const;
  FX_FLOAT a;
  FX_FLOAT b;
  FX_FLOAT c;
  FX_FLOAT d;
  FX_FLOAT e;
  FX_FLOAT f;
  FX_FLOAT g;
  FX_FLOAT h;
  FX_FLOAT i;
};

//Keep old symbol
#define CFX_AffineMatrix  CFX_Matrix

//<<<+++OPENSOURCE_MUST_BEGIN
#endif //_FXCRT_COORDINATES_
//<<<+++OPENSOURCE_MUST_END

/** @} */

//<<<+++OPENSOURCE_END
