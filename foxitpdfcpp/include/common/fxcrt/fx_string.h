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
 * @file fx_string.h
 * @brief Header file for Strings, variable-length sequence of characters.
 *        There are two strings here, byte-string and wide-string
 */

//<<<+++OPENSOURCE
//<<<+++OPENSOURCE_LICENSE
//<<<+++OPENSOURCE_BEGIN LIC==FOXIT||LIC==GOOGLE

/**
 * @addtogroup FXCRT
 * @{
 */

//<<<+++OPENSOURCE_MUST_BEGIN
#ifndef _FX_STRING_H_
#define _FX_STRING_H_
//<<<+++OPENSOURCE_MUST_END

class CFX_ByteStringC;
class CFX_ByteString;
class CFX_WideStringC;
class CFX_WideString;
struct CFX_CharMap;
class CFX_BinaryBuf;

/** @brief String size is limited to 2^31-1. */
typedef int FX_STRSIZE;

class CFX_ByteStringL;
class CFX_WideStringL;

//*****************************************************************************
//* CFX_ByteStringC - constant byte string
//*****************************************************************************
/**
 * @brief CONSTANT BYTE STRING CLASS
 *
 * @details Constant byte string, it contains no buffer so its content cannot be changed directly.
 */
class CFX_ByteStringC : public CFX_Object
{
 public:
  /**
   * @brief Constructs a null constant string.
   */
  CFX_ByteStringC()
  {
    m_Ptr = NULL;
    m_Length = 0;
  }
  /**
   * @brief Constructs from a byte string.
   *
   * @param[in] ptr   Pointer to a constant byte string.
   * @param[in] size  The length of the byte string.
   */
  CFX_ByteStringC(FX_LPCBYTE ptr, FX_STRSIZE size)
  {
    m_Ptr = ptr;
    m_Length = size;
  }
//<<<+++OPENSOURCE_MUST_BEGIN LIC==FOXIT
#ifndef _NO_LPCSTR_SUPPORT_
//<<<+++OPENSOURCE_MUST_END
  /**
   * @brief Construct from a character string.
   *
   * @param[in] ptr  Pointer to a constant character string, the string must be null-terminated.
   */
  CFX_ByteStringC(FX_LPCSTR ptr)
  {
    m_Ptr = (FX_LPCBYTE)ptr;
    m_Length = ptr ? (FX_STRSIZE)FXSYS_strlen(ptr) : 0;
  }
//<<<+++OPENSOURCE_MUST_BEGIN LIC==FOXIT
#endif
//<<<+++OPENSOURCE_MUST_END
  /**
   * @brief Construct from a single character.
   *
   * @param[in] ch  A single character.
   */
  explicit CFX_ByteStringC(const FX_CHAR& ch)
  {
    m_Ptr = (FX_LPCBYTE)&ch;
    m_Length = 1;
  }
  /**
   * @brief Construct from a character string.
   *
   * @param[in] ptr  Pointer to a constant character string.
   * @param[in] len  The length of the character string. This can be -1 for null-terminated string.
   */
  CFX_ByteStringC(FX_LPCSTR ptr, FX_STRSIZE len)
  {
    m_Ptr = (FX_LPCBYTE)ptr;
    if (len == -1)
      m_Length = (FX_STRSIZE)FXSYS_strlen(ptr);
    else
      m_Length = len;
  }
  /**
   * @brief Copy constructor
   *
   * @param[in] src  constant ref to a CFX_ByteStringC object.
   */
  CFX_ByteStringC(const CFX_ByteStringC& src)
  {
    m_Ptr = src.m_Ptr;
    m_Length = src.m_Length;
  }
  /**
   * @brief Construct from a byte string.
   *
   * @param[in] src  constant ref to a CFX_ByteString object.
   */
  CFX_ByteStringC(const CFX_ByteString& src);

  /**
   * @brief Assignment(=) operator overload. From a character string.
   *
   * @param[in] src  Pointer to a constant character string.
   *
   * @return A reference to current object itself.
   */
  CFX_ByteStringC& operator = (FX_LPCSTR src)
  {
    m_Ptr = (FX_LPCBYTE)src;
    m_Length = m_Ptr ? (FX_STRSIZE)FXSYS_strlen(src) : 0;
    return *this;
  }
  /**
   * @brief Assignment(=) operator overload. From a CFX_ByteStringC object.
   *
   * @param[in] src  constant ref to a CFX_ByteStringC object.
   *
   * @return A reference to current object itself.
   */
  CFX_ByteStringC& operator = (const CFX_ByteStringC& src)
  {
    m_Ptr = src.m_Ptr;
    m_Length = src.m_Length;
    return *this;
  }
  /**
   * @brief Assignment(=) operator overload. From a CFX_ByteString object.
   *
   * @param[in] src  constant ref to a CFX_ByteString object.
   *
   * @return A reference to current object itself.
   */
  CFX_ByteStringC& operator = (const CFX_ByteString& src);

  /**
   * @brief Comparison(==) operator overload. case-sensitive.
   *
   * @param[in] str  constant ref to a CFX_ByteStringC object.
   *
   * @return <b>true</b> means equal, while <b>false</b> means not equal.
   */
  bool      operator == (const CFX_ByteStringC& str) const
  {
    return   str.m_Length == m_Length && FXSYS_memcmp32(str.m_Ptr, m_Ptr, m_Length) == 0;
  }
  /**
   * @brief Comparison(!=) operator overload. case-sensitive.
   *
   * @param[in] str  constant ref to a CFX_ByteStringC object.
   *
   * @return <b>true</b> means not equal, while <b>false</b> means equal.
   */
  bool      operator != (const CFX_ByteStringC& str) const
  {
    return   str.m_Length != m_Length || FXSYS_memcmp32(str.m_Ptr, m_Ptr, m_Length) != 0;
  }

/** @brief Construct a ID from four integer values. */
#define FXBSTR_ID(c1, c2, c3, c4) ((c1 << 24) | (c2 << 16) | (c3 << 8) | (c4))

  /**
   * @brief Get a DWORD identifier of the string, from a particular position.
   *
   * @details This DWORD can be used for quick comparison. Using MSB-first scheme. If the string does not
   *          have enough bytes, then zero will be used missing bytes.
   *
   * @param[in] start_pos  Start position in the constant byte string.
   *
   * @return A DWORD identifier.
   *
   * @note For example:
   * @code
   *    CFX_ByteString str1("hello"), str2("hey");
   *    FX_BOOL bCheck1 = str1.GetID() == FXBSTR_ID('h', 'e', 'l', 'l');  // returns TRUE
   *    FX_BOOL bCheck2 = str2.GetID() == FXBSTR_ID('h', 'e', 'y', 0);  // returns TRUE
   * @endcode
   */
  FX_DWORD    GetID(FX_STRSIZE start_pos = 0) const;

  /**
   * @brief Get a constant byte string pointer to the byte string.
   *
   * @return A constant byte string pointer to the byte string.
   */
  FX_LPCBYTE    GetPtr() const { return m_Ptr; }
  /**
   * @brief Get a constant character string pointer to the byte string.
   *
   * @return A constant character string pointer to the byte string.
   */
  FX_LPCSTR    GetCStr() const { return (FX_LPCSTR)m_Ptr; }
  /**
   * @brief Get the length of the byte string.
   *
   * @return The length of the byte string.
   */
  FX_STRSIZE    GetLength() const { return m_Length; }
  /**
   * @brief Check whether current string object is empty.
   *
   * @return <b>true</b> means current string object is empty, while <b>false</b> means not.
   */
  bool      IsEmpty() const { return m_Length == 0; }

  /**
   * @brief This casting operator accesses the byte string referred in a CFX_ByteStringC object.
   *
   * @return A byte string pointer to the data in the string.
   *
   * @note A CFX_ByteStringC cannot be implicitly converted to a FX_LPCSTR pointer,
   *       because very likely the CFX_ByteStringC buffer is not null-terminated.
   */
  operator    FX_LPCBYTE() const { return m_Ptr; }

  /**
   * @brief This method retrieves a single byte specified by an index number.
   *
   * @param[in] index  Specifies the zero-based index in the byte string.
   *
   * @return A single byte.
   */
  FX_BYTE      GetAt(FX_STRSIZE index) const { return m_Ptr[index]; }

  /**
   * @brief This method extracts a substring of length count bytes from this CFX_ByteStringC object,
   *        starting at position index (zero-based).
   *
   * @param[in] index  Specifies the zero-based index in the CFX_ByteStringC object.
   * @param[in] count  Specifies the number of bytes to extract from this CFX_ByteStringC object.
   *
   * @return A CFX_ByteStringC object refer to the substring.
   */
  CFX_ByteStringC  Mid(FX_STRSIZE index, FX_STRSIZE count = -1) const
  {
    if (index < 0) index = 0;
    if (index > m_Length) return CFX_ByteStringC();
    if (count < 0 || count > m_Length - index) count = m_Length - index;
    return CFX_ByteStringC(m_Ptr + index, count);
  }

 protected:
  /* The constant byte string pointer. */
  FX_LPCBYTE    m_Ptr;
  /* The length in bytes of the byte string. */
  FX_STRSIZE    m_Length;

 private:
  /*
   * "new" operator forbidden. Cannot allocate a CFX_ByteStringC in heap.
   */
  void*      operator new (size_t) throw() { return NULL; }
};

/** @brief A reference to a constant CFX_ByteStringC object. */
typedef const CFX_ByteStringC& FX_BSTR;

/**
 * @brief All application should use the following macro when specifying a string constant.
 * "str" must be a character string constant.
 *
 * @note For example:
 * @code
 *    FX_BSTRC("abc").
 * @endcode
 */
#define FX_BSTRC(str) CFX_ByteStringC(str, sizeof str-1)

//*****************************************************************************
//* CFX_ByteString - byte string
//*****************************************************************************
/** @brief This class represents the data of a byte string object. */
struct CFX_StringData
{
  /** @brief Reference count. */
  long    m_nRefs;
  /** @brief Length of data (excluding terminator). */
  FX_STRSIZE  m_nDataLength;
  /** @brief Length of allocation. */
  FX_STRSIZE  m_nAllocLength;
  /** @brief Real data (actually a variable-sized array). */
  FX_CHAR    m_String[1];
};

/**
 * @brief BYTE STRING CLASS
 */
class CFX_ByteString : public CFX_Object
{
 public:
  /**
   * @brief Construct a null byte string.
   */
  CFX_ByteString() { m_pData = NULL; }
  /**
   * @brief Copy constructor.
   *
   * @param[in] str  A constant ref to a CFX_ByteString object.
   */
  CFX_ByteString(const CFX_ByteString& str);
  /**
   * @brief Construct from a single character.
   *
   * @param[in] ch  A single character.
   */
  explicit CFX_ByteString(char ch);
  /**
   * @brief Construct from a character string.
   *
   * @param[in] ptr  Pointer to a constant character string.
   * @param[in] len  The length of the character string. len can be -1 for zero terminated string.
   */
  CFX_ByteString(FX_LPCSTR ptr, FX_STRSIZE len=-1);
  /**
   * @brief Construct from a byte string.
   *
   * @param[in] ptr  Pointer to a constant byte string.
   * @param[in] len  The length of the byte string.
   */
  CFX_ByteString(FX_LPCBYTE ptr, FX_STRSIZE len);
  /**
   * @brief Construct from a constant ref to a CFX_ByteStringC object.
   *
   * @param[in] bstrc  A constant ref to a CFX_ByteStringC object.
   */
  CFX_ByteString(FX_BSTR bstrc);
  /**
   * @brief Concatenate constructor.
   *
   * @param[in] bstrc1  Fist constant ref to a CFX_ByteStringC object.
   * @param[in] bstrc2  Second constant ref to a CFX_ByteStringC object.
   */
  CFX_ByteString(FX_BSTR bstrc1, FX_BSTR bstrc2);
  /**
   * Destructor.
   */
  ~CFX_ByteString();

  /**
   * @brief Create a CFX_ByteString object from a Unicode string. Convert from Unicode to system multi-byte charset.
   *
   * @param[in] ptr  Pointer to a constant Unicode string.
   * @param[in] len  The length of the Unicode string. len can be -1 for zero terminated Unicode string.
   *
   * @return A byte string.
   */
  static CFX_ByteString  FromUnicode(FX_LPCWSTR ptr, FX_STRSIZE len = -1);
  /**
   * @brief Create a CFX_ByteString object from a CFX_WideString object.
   *
   * @param[in] str  A ref to a constant CFX_WideString object.
   *
   * @return A byte string.
   */
  static CFX_ByteString  FromUnicode(const CFX_WideString& str);

//<<<+++OPENSOURCE_MUST_END

  /**
   * @brief FX_LPCSTR type conversion operator. CFX_ByteString can be used in places where FX_LPCSTR or FX_LPCBYTE is needed.
   */
  operator        FX_LPCSTR() const { return m_pData ? m_pData->m_String : ""; }
  /**
   * @brief FX_LPCBYTE type conversion operator. CFX_ByteString can be used in places where FX_LPCSTR or FX_LPCBYTE is needed.
   */
  operator        FX_LPCBYTE() const { return m_pData ? (FX_LPCBYTE)m_pData->m_String : NULL; }

  /**
   * @brief Get number of bytes in the byte string (not counting any possible terminator).
   *
   * @return The Length of the byte string.
   */
  FX_STRSIZE        GetLength() const { return m_pData ? m_pData->m_nDataLength : 0; }

  /**
   * @brief Check whether current string object is empty.
   *
   * @return <b>true</b> means current string object is empty, while <b>false</b> means not.
   */
  bool          IsEmpty() const { return !GetLength(); }
  /**
   * @brief Compare the the string with another. Case-sensitive.
   *
   * @param[in] str  The byte string to be compared.
   *
   * @return <ul>
   *         <li>-1 means current string is "smaller" (in alphabetic order) than the other one.</li>
   *         <li>0 means equal.</li>
   *         <li>1 means current string is "larger" (in alphabetic order) than the other one.</li>
   *         </ul>
   */
  int            Compare(FX_BSTR str) const;

  /**
   * @brief Check if current string is equal to another one. Case-sensitive.
   *
   * @details This function is faster than function {@link CFX_ByteString::Compare} if only need to check
   *          whether two strings are equal.
   *
   * @param[in] str  The byte string to be compared.
   *
   * @return <b>true</b> means current string is equal to the other one, while <b>false</b> means not.
   */
  bool          Equal(FX_BSTR str) const;

  /**
   * @brief Check if current string is equal to another one, not considering case.
   *
   * @details This function will treat letters 'A'-'Z' just same as 'a'-'z'.
   *
   * @param[in] str  The byte string to be compared.
   *
   * @return <b>true</b> means current string is equal to the other one, while <b>false</b> means not.
   */
  bool          EqualNoCase(FX_BSTR str) const;

//<<<+++OPENSOURCE_MUST_BEGIN LIC==FOXIT
#ifndef _NO_LPCSTR_SUPPORT_
//<<<+++OPENSOURCE_MUST_END
  /**
   * @brief Comparison(==) operator overload. case-sensitive.
   *
   * @param[in] str  The null-terminated character string to be compared.
   *
   * @return <b>true</b> means equal, while <b>false</b> means not equal.
   */
  bool          operator == (FX_LPCSTR str) const { return Equal(str); }
//<<<+++OPENSOURCE_MUST_BEGIN LIC==FOXIT
#endif
//<<<+++OPENSOURCE_MUST_END
  /**
   * @brief Comparison(==) operator overload. case-sensitive.
   *
   * @param[in] str  The null-terminated constant byte string to be compared.
   *
   * @return <b>true</b> means equal, while <b>false</b> means not equal.
   */
  bool          operator == (FX_BSTR str) const { return Equal(str); }
  /**
   * @brief Comparison(==) operator overload. case-sensitive.
   *
   * @param[in] str  The null-terminated byte string to be compared.
   *
   * @return <b>true</b> means equal, while <b>false</b> means not equal.
   */
  bool          operator == (const CFX_ByteString& str) const;
//<<<+++OPENSOURCE_MUST_BEGIN LIC==FOXIT
#ifndef _NO_LPCSTR_SUPPORT_
//<<<+++OPENSOURCE_MUST_END
  /**
   * @brief Comparison(!=) operator overload. case-sensitive.
   *
   * @param[in] str  The null-terminated character string to be compared.
   *
   * @return <b>true</b> means not equal, while <b>false</b> means equal.
   */
  bool          operator != (FX_LPCSTR str) const { return !Equal(str); }
//<<<+++OPENSOURCE_MUST_BEGIN LIC==FOXIT
#endif
//<<<+++OPENSOURCE_MUST_END
  /**
   * @brief Comparison(!=) operator overload. case-sensitive.
   *
   * @param[in] str  The null-terminated constant byte string to be compared.
   *
   * @return <b>true</b> means not equal, while <b>false</b> means equal.
   */
  bool          operator != (FX_BSTR str) const { return !Equal(str); }
  /**
   * @brief Comparison(!=) operator overload. case-sensitive.
   *
   * @param[in] str  The null-terminated byte string to be compared.
   *
   * @return <b>true</b> means not equal, while <b>false</b> means equal.
   */
  bool          operator != (const CFX_ByteString& str) const { return !operator==(str); }

  /**
   * @brief Comparison(<) operator overload. case-sensitive.
   *
   * @param[in] rhs  The right hand side string.
   *
   * @return <b>true</b> means current string is smaller than parameter <i>rhs</i>, while <b>false</b> means not.
   */
  bool          operator< (const CFX_ByteString& rhs) const;

  /**
   * @brief Set this string to be empty.
   *
   * @return None.
   */
  void          Empty();

  /**
   * @brief Assignment(=) operator overload. From a character string.
   *
   * @param[in] str  A pointer to a constant character string.
   *
   * @return A reference to current object itself.
   */
  const CFX_ByteString&  operator = (FX_LPCSTR str);
  /**
   * @brief Assignment(=) operator overload. From a constant byte string.
   *
   * @param[in] bstrc  A ref to a constant byte string.
   *
   * @return A reference to current object itself.
   */
  const CFX_ByteString&  operator = (FX_BSTR bstrc);
  /**
   * @brief Assignment(=) operator overload. From a CFX_ByteString object.
   *
   * @param[in] stringSrc  A ref to a constant CFX_ByteString object.
   *
   * @return A reference to current object itself.
   */
  const CFX_ByteString&  operator = (const CFX_ByteString& stringSrc);
  /**
   * @brief Assignment(=) operator overload. From a CFX_BinaryBuf object.
   *
   * @param[in] buf  A ref to a constant CFX_BinaryBuf object.
   *
   * @return A reference to current object itself.
   */
  const CFX_ByteString&  operator = (const CFX_BinaryBuf& buf);

  /**
   * @brief Load from a byte string.
   *
   * @param[in] str  Pointer to a constant byte string.
   * @param[in] len  The length of the byte string.
   *
   * @return None.
   */
  void          Load(FX_LPCBYTE str, FX_STRSIZE len);

  /**
   * @brief Concatenation(+=) operator overload. Concatenate a single character.
   *
   * @param[in] ch  A single character.
   *
   * @return A reference to current object itself.
   */
  const CFX_ByteString&  operator += (FX_CHAR ch);
  /**
   * @brief Concatenation(+=) operator overload. Concatenate a null-terminated character string.
   *
   * @param[in] str  Pointer to a constant null-terminated character string.
   *
   * @return A reference to current object itself.
   */
  const CFX_ByteString&  operator += (FX_LPCSTR str);
  /**
   * @brief Concatenation(+=) operator overload. Concatenate a CFX_ByteString object.
   *
   * @param[in] str  A ref to a constant CFX_ByteString object.
   *
   * @return A reference to current object itself.
   */
  const CFX_ByteString&  operator += (const CFX_ByteString& str);
  /**
   * @brief Concatenation(+=) operator overload. Concatenate a constant CFX_ByteStringC object.
   *
   * @param[in] bstrc  A ref to a constant CFX_ByteStringC object.
   *
   * @return A reference to current object itself.
   */
  const CFX_ByteString&  operator += (FX_BSTR bstrc);

  /**
   * @brief Get a single byte specified by an index number.
   *
   * @param[in] nIndex  Specifies the zero-based index in the byte string.
   *
   * @return A single byte.
   */
  FX_BYTE          GetAt(FX_STRSIZE nIndex) const { return m_pData ? m_pData->m_String[nIndex] : 0; }
  /**
   * @brief Subscript([]) operator overload. It retrieves a single byte specified by the zero-based index in nIndex.
   *
   * @param[in] nIndex  Specifies the zero-based index in the byte string.
   *
   * @return A single byte.
   */
  FX_BYTE          operator[](FX_STRSIZE nIndex) const { return m_pData ? m_pData->m_String[nIndex] : 0; }
  /**
   * @brief Overwrites a single byte specified by an index number.
   *
   * @param[in] nIndex  Specifies the zero-based index in the byte string.
   * @param[in] ch      A single character.
   *
   * @return None.
   */
  void          SetAt(FX_STRSIZE nIndex, FX_CHAR ch);

  /**
   * @brief Insert a character before specific position.
   *
   * @param[in] index  Specifies the zero-based index in the byte string.
   * @param[in] ch     A single character.
   *
   * @return The new length of the byte string.
   */
  FX_STRSIZE        Insert(FX_STRSIZE index, FX_CHAR ch);

  /**
   * @brief Delete one or more characters starting from specific position.
   *
   * @param[in] index  Specifies the zero-based index in the byte string for starting deleting.
   * @param[in] count  Count of bytes to be deleted.
   *
   * @return The new length of the byte string.
   */
  FX_STRSIZE        Delete(FX_STRSIZE index, FX_STRSIZE count = 1);
  /**
   * @brief Format a number of parameters into this byte string.
   *
   * @details On desktop platforms, this function supports all the sprintf() formats.<br>
   *          On embedded platforms, it supports only a subset of formats:
   *          <ul>
   *          <li>Supported types: d, u, f, g, x, X, s, c, %.</li>
   *          <li>Width field supported.</li>
   *          <li>Precision not supported</li>
   *          <li>Flags supported: '0'.</li>
   *          </ul>
   *
   * @param[in] lpszFormat  Specifies a format-control string.
   *
   * @return None.
   */
  void          Format(FX_LPCSTR lpszFormat, ... );
  /**
   *  @brief Format a number of parameters into this byte string, using va_list.
   *
   * @param[in] lpszFormat  Specifies a format-control string.
   * @param[in] argList     Variable-argument lists.
   *
   * @return None.
   *
   * @see CFX_ByteString::Format
   */
  void          FormatV(FX_LPCSTR lpszFormat, va_list argList);
  /**
   * @brief Reserve a buffer that can hold specific number of bytes.
   *
   * @details The content of this string won't be changed. This can be used if application anticipates
   *          the string may grow many times, in this case, reserving a larger buffer will support string growth
   *          without buffer reallocation.
   *
   * @param[in] len  Length expected to reserve.
   *
   * @return None.
   */
  void          Reserve(FX_STRSIZE len);

  /**
   * @brief Get a buffer with specific number of bytes allocated.
   *
   * @details The content of this string won't be affected by function {@link CFX_ByteString::GetBuffer}.
   *          Caller can modified the returned buffer, and should call function {@link CFX_ByteString::ReleaseBuffer}
   *          after modification done.
   *
   * @param[in] len  the Length expected to get.
   *
   * @return A character string pointer to the byte string.
   */
  FX_LPSTR        GetBuffer(FX_STRSIZE len);

  /**
   * @brief Lock and get the current string buffer, so the caller can modify the returned buffer.
   *
   * @details Caller can modified the returned buffer, and should call function {@link CFX_ByteString::ReleaseBuffer}
   *          after modification done.
   *
   * @return A character string pointer to the byte string.
   */
  FX_LPSTR        LockBuffer();

  /**
   * @brief Release the buffer fetched by function {@link CFX_ByteString::GetBuffer} or
   *        {@link CFX_ByteString::LockBuffer}, and set the length of modified string.
   *
   *@details If parameter <i>len</i> parameter is -1, then it's assumed to be a zero-terminated string.
   *
   * @param[in] len  Length expected to release to. Default value: -1.
   *
   * @return None.
   */
  void          ReleaseBuffer(FX_STRSIZE len = -1);

  /**
   * @brief Extracts a substring from this CFX_ByteString object, starting at position nFirst (zero-based) to last.
   *
   * @param[in] first  Specifies the zero-based index of the starting position in this CFX_ByteString object.
   *
   * @return A CFX_ByteString sub-string.
   */
  CFX_ByteString      Mid(FX_STRSIZE first) const;
  /**
   * @brief Extracts a substring of count bytes from this CFX_ByteString object, starting at position nFirst (zero-based) to last.
   *
   * @param[in] first  Specifies the zero-based index of the starting position in this CFX_ByteString object.
   * @param[in] count  The count of bytes expected to extract for the sub-string.
   *
   * @return A CFX_ByteString sub-string.
   */
  CFX_ByteString      Mid(FX_STRSIZE first, FX_STRSIZE count) const;
  /**
   * @brief Extracts the first (leftmost) count bytes from this CFX_ByteString object as a sub-string.
   *
   * @param[in] count  The count of bytes expected to extract for the sub-string.
   *
   * @return A CFX_ByteString sub-string.
   */
  CFX_ByteString      Left(FX_STRSIZE count) const;
  /**
   * @brief Extracts the last (rightmost) count bytes from this CFX_ByteString object as a sub-string.
   *
   * @param[in] count  The count of bytes expected to extract for the sub-string.
   *
   * @return A CFX_ByteString sub-string.
   */
  CFX_ByteString      Right(FX_STRSIZE count) const;
  /**
   * @brief Find a sub-string, from specific position. Only first occurrence is found.
   *
   * @param[in] lpszSub  The sub-string to be found.
   * @param[in] start    Specifies the zero-based index of the starting position to do finding.
   *
   * @retval The position where first occurrence is found. -1 means not found.
   */
  FX_STRSIZE        Find(FX_BSTR lpszSub, FX_STRSIZE start=0) const;
  /**
   * @brief Find a character, from specific position. Only first occurrence is found.
   *
   * @param[in] ch     The character to be found.
   * @param[in] start  Specifies the zero-based index of the starting position to do finding.
   *
   * @retval The position where first occurrence is found. -1 means not found.
   */
  FX_STRSIZE        Find(FX_CHAR ch, FX_STRSIZE start=0) const;
  /**
   * @brief Find a character from end of the string
   *
   * @param[in] ch  A character to be found in curren string, from the end.
   *
   * @return The position of input character in current string. -1 means Not found.
   */
  FX_STRSIZE        ReverseFind(FX_CHAR ch) const;

  /**
   * @brief Change case of English letters to lower.
   *
   * @return None.
   */
  void          MakeLower();
  /**
   * @brief Change case of English letters to upper.
   *
   * @return None.
   */
  void          MakeUpper();

  /**
   * @brief Trim white spaces from the right side of the byte string.
   *
   * @return None.
   */
  void          TrimRight();
  /**
   * @brief Trim continuous occurrences of specified character from right side of the byte string.
   *
   * @param[in] chTarget  The specified character.
   *
   * @return None.
   */
  void          TrimRight(FX_CHAR chTarget);
  /**
   * @brief Trim continuous occurrences of specified characters from right side of the byte string.
   *
   * @param[in] lpszTargets  The specified characters.
   *
   * @return None.
   */
  void          TrimRight(FX_BSTR lpszTargets);
  /**
   * @brief Trim white spaces from the left side of the byte string.
   *
   * @return None.
   */
  void          TrimLeft();
  /**
   * @brief Trim continuous occurrences of specified characters from left side of the byte string.
   *
   * @param[in] chTarget  The specified character.
   *
   * @return None.
   */
  void          TrimLeft(FX_CHAR chTarget);
  /**
   * @brief Trim continuous occurrences of specified characters from left side of the byte string.
   *
   * @param[in] lpszTargets  The specified characters.
   *
   * @return None.
   */
  void          TrimLeft(FX_BSTR lpszTargets);

  /**
   * @brief Replace all patterns in the string with a new sub-string.
   *
   * @param[in] lpszOld  Specified the string to be matched and replaced in the byte string.
   * @param[in] lpszNew  Specified the string to replace.
   *
   * @return The number of replaced patterns.
   */
  FX_STRSIZE        Replace(FX_BSTR lpszOld, FX_BSTR lpszNew);
  /**
   * @brief Remove all occurrence of a particular character.
   *
   * @param[in] ch  Specified the character to be removed.
   *
   * @return The number of characters removed.
   */
  FX_STRSIZE        Remove(FX_CHAR ch);

  /**
   * @brief Decode a UTF-8 unicode string (assume this byte string is UTF-8 encoded).
   *
   * @return A unicode string.
   */
  CFX_WideString      UTF8Decode() const;

  /**
   * @brief Load unicode data into this byte string, using specified character mapper.
   *        If no character mapper specified, the system default mapper will be used.
   *
   * @param[in] str       The input unicode string.
   * @param[in] pCharMap  Specified character mapper to be used for converting.
   *
   * @return None.
   */
  void          ConvertFrom(const CFX_WideString& str, CFX_CharMap* pCharMap = NULL);
  /**
   * @brief Get a DWORD identifier of the string. See function {@link CFX_ByteStringC::GetID} for details.
   *
   * @param[in] start_pos  Start position in the constant byte string.
   *
   * @return A FX_DWORD identifier.
   */
  FX_DWORD        GetID(FX_STRSIZE start_pos = 0) const;
  /**
   * @brief Load the whole content of a file.
   *
   * @param[in] file_path  The file path.
   *
   * @return A CFX_ByteString object.
   */
  static CFX_ByteString  LoadFromFile(FX_BSTR file_path);

/** @brief For formating integer: the value is signed. */
#define FXFORMAT_SIGNED      1
/** @brief For formating integer: using hexadecimal  format */
#define FXFORMAT_HEX      2
/** @brief For formating integer: using with FXFORMAT_HEX to produce capital hexadecimal letters */
#define FXFORMAT_CAPITAL    4

  /**
   * @brief Convert from Integer.
   *
   * @details The flags can be following flags (single or compound):
   *          <ul>
   *          <li>FXFORMAT_SIGNED</li>
   *          <li>FXFORMAT_HEX</li>
   *          <li>FXFORMAT_CAPITAL</li>
   *          </ul>
   *
   * @param[in] i      The input 32-bit integer.
   * @param[in] flags  The formating flags. Default value: 0.
   *
   * @return A CFX_ByteString object.
   */
  static CFX_ByteString  FormatInteger(FX_INT32 i, FX_DWORD flags = 0);
  /**
   * @brief Convert from floating-point number.
   *
   * @param[in] f          The input floating-point number.
   * @param[in] precision  The number of decimal digits. Not used. Default value: 0.
   *
   * @return A CFX_ByteString object.
   *
   * @todo We need a better algorithm and to support precision.
   */
  static CFX_ByteString  FormatFloat(FX_FLOAT f, int precision = 0);

 protected:
  /* Pointer to ref counted byte string data. */
  struct CFX_StringData*  m_pData;

  void          AllocCopy(CFX_ByteString& dest, FX_STRSIZE nCopyLen, FX_STRSIZE nCopyIndex, FX_STRSIZE nExtraLen) const;
  void          AssignCopy(FX_STRSIZE nSrcLen, FX_LPCSTR lpszSrcData);
  void          ConcatCopy(FX_STRSIZE nSrc1Len, FX_LPCSTR lpszSrc1Data, FX_STRSIZE nSrc2Len, FX_LPCSTR lpszSrc2Data);
  void          ConcatInPlace(FX_STRSIZE nSrcLen, FX_LPCSTR lpszSrcData);
  void          CopyBeforeWrite();
  void          AllocBeforeWrite(FX_STRSIZE nLen);
};

inline CFX_ByteStringC::CFX_ByteStringC(const CFX_ByteString& src)
{
  m_Ptr = (FX_LPCBYTE)src;
  m_Length = src.GetLength();
}

inline CFX_ByteStringC& CFX_ByteStringC::operator = (const CFX_ByteString& src)
{
  m_Ptr = (FX_LPCBYTE)src;
  m_Length = src.GetLength();
  return *this;
}

/**
 * @name Byte string concatenation operation
 * 
 * @details Both side of the concatenation operator (+) can be:
 *          <ul>
 *          <li>A buffered byte string (const CFX_ByteString&);</li>
 *          <li>A non-buffered byte string (const CFX_ByteStringC&, a.k.a FX_BSTR);</li>
 *          <li>A zero-terminated C-style string (FX_LPCSTR);</li>
 *          <li>A single character or byte (FX_CHAR);</li>
 *          </ul>
 */
 /*@{*/

/**
 * @brief Concatenate a non-buffered byte string and a non-buffered byte string.
 *
 * @param[in] str1  A non-buffered byte string.
 * @param[in] str2  A non-buffered byte string.
 *
 * @return A CFX_ByteString object.
 */
inline CFX_ByteString operator + (FX_BSTR str1, FX_BSTR str2) { return CFX_ByteString(str1, str2); }
//<<<+++OPENSOURCE_MUST_BEGIN LIC==FOXIT
#ifndef _NO_LPCSTR_SUPPORT_
//<<<+++OPENSOURCE_MUST_END
/**
 * @brief Concatenate a non-buffered byte string and a zero-terminated C-style string
 *
 * @param[in] str1  A non-buffered byte string.
 * @param[in] str2  A zero-terminated C-style string.
 *
 * @return A CFX_ByteString object.
 */
inline CFX_ByteString operator + (FX_BSTR str1, FX_LPCSTR str2) { return CFX_ByteString(str1, str2); }
/**
 * @brief Concatenate a zero-terminated C-style string and a non-buffered byte string.
 *
 * @param[in] str1  A zero-terminated C-style string.
 * @param[in] str2  A non-buffered byte string.
 *
 * @return A CFX_ByteString object.
 */
inline CFX_ByteString operator + (FX_LPCSTR str1,FX_BSTR str2) { return CFX_ByteString(str1, str2); }
//<<<+++OPENSOURCE_MUST_BEGIN LIC==FOXIT
#endif
//<<<+++OPENSOURCE_MUST_END
/**
 * @brief Concatenate a non-buffered byte string and a single character or byte.
 *
 * @param[in] str1  A non-buffered byte string.
 * @param[in] ch    A single character or byte.
 *
 * @return A CFX_ByteString object.
 */
inline CFX_ByteString operator + (FX_BSTR str1, FX_CHAR ch) { return CFX_ByteString(str1, CFX_ByteStringC(ch)); }
/**
 * @brief Concatenate a single character or byte and a non-buffered byte string.
 *
 * @param[in] ch    A single character or byte.
 * @param[in] str2  A non-buffered byte string.
 *
 * @return A CFX_ByteString object.
 */
inline CFX_ByteString operator + (FX_CHAR ch, FX_BSTR str2) { return CFX_ByteString(CFX_ByteStringC(ch), str2); }

/**
 * @brief Concatenate a buffered byte string and a buffered byte string.
 *
 * @param[in] str1  A buffered byte string.
 * @param[in] str2  A buffered byte string.
 *
 * @return A CFX_ByteString object.
 */
inline CFX_ByteString operator + (const CFX_ByteString& str1, const CFX_ByteString& str2) { return CFX_ByteString(str1, str2); }
/**
 * @brief Concatenate a buffered byte string and a single character or byte.
 *
 * @param[in] str1  A buffered byte string.
 * @param[in] ch    A single character or byte.
 *
 * @return A CFX_ByteString object.
 */
inline CFX_ByteString operator + (const CFX_ByteString& str1, FX_CHAR ch) { return CFX_ByteString(str1, CFX_ByteStringC(ch)); }
/**
 * @brief Concatenate a single character or byte and a buffered byte string.
 *
 * @param[in] ch    A single character or byte.
 * @param[in] str2  A buffered byte string.
 *
 * @return A CFX_ByteString object.
 */
inline CFX_ByteString operator + (FX_CHAR ch, const CFX_ByteString& str2) { return CFX_ByteString(CFX_ByteStringC(ch), str2); }
//<<<+++OPENSOURCE_MUST_BEGIN LIC==FOXIT
#ifndef _NO_LPCSTR_SUPPORT_
//<<<+++OPENSOURCE_MUST_END
/**
 * @brief Concatenate a buffered byte string and a zero-terminated C-style string.
 *
 * @param[in] str1  A buffered byte string.
 * @param[in] str2  A zero-terminated C-style string.
 *
 * @return A CFX_ByteString object.
 */
inline CFX_ByteString operator + (const CFX_ByteString& str1, FX_LPCSTR str2) { return CFX_ByteString(str1, str2); }
/**
 * @brief Concatenate a zero-terminated C-style string and a buffered byte string.
 *
 * @param[in] str1  A zero-terminated C-style string.
 * @param[in] str2  A buffered byte string.
 *
 * @return A CFX_ByteString object.
 */
inline CFX_ByteString operator + (FX_LPCSTR str1, const CFX_ByteString& str2) { return CFX_ByteString(str1, str2); }
//<<<+++OPENSOURCE_MUST_BEGIN LIC==FOXIT
#endif
//<<<+++OPENSOURCE_MUST_END
/**
 * @brief Concatenate a buffered byte string and a non-buffered byte string.
 *
 * @param[in] str1  A buffered byte string.
 * @param[in] str2  A non-buffered byte string.
 *
 * @return A CFX_ByteString object.
 */
inline CFX_ByteString operator + (const CFX_ByteString& str1, FX_BSTR str2) { return CFX_ByteString(str1, str2); }
/**
 * @brief Concatenate a non-buffered byte string and a buffered byte string.
 *
 * @param[in] str1  A non-buffered byte string.
 * @param[in] str2  A buffered byte string.
 *
 * @return A CFX_ByteString object.
 */
inline CFX_ByteString operator + (FX_BSTR str1, const CFX_ByteString& str2) { return CFX_ByteString(str1, str2); }

/*@}*/

/**
 * @brief A fixed string buffer holding up to certain number of characters.
 *
 * @details Operations are protected by buffer limit.
 *          Please do not use this class directly, use CFX_StringBufTemplate instead.
 */
class CFX_StringBufBase : public CFX_Object
{
 public:
  /**
   * @brief A Constructor
   *
   * @param[in] limit  buffer limit.
   */
  explicit CFX_StringBufBase(FX_STRSIZE limit) { m_Size = 0; m_Limit = limit; }

  /**
   * @brief Get a C-style string pointer to the string buffer.
   *
   * @return A C-style string pointer to the buffer.
   */
  FX_CHAR*  GetPtr() const { return (FX_CHAR*)(this + 1); }
  /**
   * @brief Gets the length of the string.
   *
   * @return The length of the string.
   */
  FX_STRSIZE  GetSize() const { return m_Size; }

  /**
   * @brief Set this string to be empty.
   *
   * @return None.
   */
  void    Empty() { m_Size = 0; }

  /**
   * @brief Copy from a non-buffered byte string.
   *
   * @param[in] str  A no-buffered byte string.
   *
   * @return None.
   */
  void    Copy(FX_BSTR str);

  /**
   * @brief Append a non-buffered byte string.
   *
   * @param[in] str  A non-buffered byte string.
   *
   * @return None.
   */
  void    Append(FX_BSTR str);

  /**
   * @brief Append an integer. See FXFORMAT_xxx for flags.
   *
   * @param[in] i      The input integer.
   * @param[in] flags  The formating flags.
   *
   * @return None.
   *
   * @see CFX_ByteString::FormatInteger
   */
  void    Append(int i, FX_DWORD flags = 0);

  /**
   * @brief Get a non-buffered byte string.
   *
   * @return A non-buffered byte string.
   */
  CFX_ByteStringC    GetStringC() const { return CFX_ByteStringC((FX_CHAR*)(this + 1), m_Size); }
  /**
   * @brief Get a buffered byte string.
   *
   * @return A buffered byte string.
   */
  CFX_ByteString    GetString() const { return CFX_ByteString((FX_CHAR*)(this + 1), m_Size); }

 protected:
  /* The buffer limit. */
  FX_STRSIZE  m_Limit;
  /* The string size. */
  FX_STRSIZE  m_Size;
  // the real buffer follows
};

/**
 * @brief A fixed string buffer template.
 */
template<FX_STRSIZE limit>
class CFX_StringBufTemplate : public CFX_StringBufBase
{
 public:
  /**
   * @brief A constructor.
   */
  CFX_StringBufTemplate() : CFX_StringBufBase(limit) {FXSYS_memset32(m_Buffer, 0, limit * sizeof(FX_CHAR));}

  /**
   * @brief The fixed string buffer.
   *
   * @note IMPORTANT: the string is NOT zero terminated.
   */
  FX_CHAR    m_Buffer[limit];
};

/** @brief A fixed 256-byte string buffer. */
typedef CFX_StringBufTemplate<256> CFX_StringBuf256;

//*****************************************************************************
//* CFX_WideStringC - constant wide string
//*****************************************************************************
/**
 * @brief CONSTANT WIDE STRING CLASS
 *
 * @details Constant wide string, it contains no buffer so its content can't be changed directly.
 */
class CFX_WideStringC : public CFX_Object
{
 public:
  /**
   * @brief Constructs a null constant string.
   */
  CFX_WideStringC()
  {
    m_Ptr = NULL;
    m_Length = 0;
  }
//<<<+++OPENSOURCE_MUST_BEGIN LIC==FOXIT
#ifndef _NO_LPCSTR_SUPPORT_
//<<<+++OPENSOURCE_MUST_END
  /**
   * @brief Construct from a character string.
   *
   * @param[in] ptr  Pointer to a constant character string, the string must be null-terminated.
   */
  CFX_WideStringC(FX_LPCWSTR ptr)
  {
    m_Ptr = ptr;
    m_Length = ptr ? (FX_STRSIZE)FXSYS_wcslen(ptr) : 0;
  }
//<<<+++OPENSOURCE_MUST_BEGIN LIC==FOXIT
#endif
//<<<+++OPENSOURCE_MUST_END
  /**
   * @brief Construct from a single character.
   *
   * @param[in] ch  A single character.
   */
  CFX_WideStringC(FX_WCHAR& ch)
  {
    m_Ptr = &ch;
    m_Length = 1;
  }
  /**
   * @brief Construct from a character string.
   *
   * @param[in] ptr  Pointer to a constant character string.
   * @param[in] len  The length of the character string. This can be -1 for null-terminated string.
   */
  CFX_WideStringC(FX_LPCWSTR ptr, FX_STRSIZE len)
  {
    m_Ptr = ptr;
    if (len == -1)
      m_Length = (FX_STRSIZE)FXSYS_wcslen(ptr);
    else
      m_Length = len;
  }
  /**
   * @brief Copy constructor
   *
   * @param[in] src  constant ref to a CFX_WideStringC object.
   */
  CFX_WideStringC(const CFX_WideStringC& src)
  {
    m_Ptr = src.m_Ptr;
    m_Length = src.m_Length;
  }
  /**
   * @brief Construct from a wide string.
   *
   * @param[in] src  constant ref to a CFX_ByteString object.
   */
  CFX_WideStringC(const CFX_WideString& src);

  /**
   * @brief Assignment(=) operator overload. From a character string.
   *
   * @param[in] src  Pointer to a constant character string.
   *
   * @return A reference to current object itself.
   */
  CFX_WideStringC& operator = (FX_LPCWSTR src)
  {
    m_Ptr = src;
    m_Length = (FX_STRSIZE)FXSYS_wcslen(src);
    return *this;
  }
  /**
   * @brief Assignment(=) operator overload. From a CFX_WideStringC object.
   *
   * @param[in] src  constant ref to a CFX_ByteStringC object.
   *
   * @return A reference to current object itself.
   */
  CFX_WideStringC& operator = (const CFX_WideStringC& src)
  {
    m_Ptr = src.m_Ptr;
    m_Length = src.m_Length;
    return *this;
  }
  /**
   * @brief Assignment(=) operator overload. From a CFX_ByteString object.
   *
   * @param[in] src  constant ref to a CFX_ByteString object.
   *
   * @return A reference to current object itself.
   */
  CFX_WideStringC& operator = (const CFX_WideString& src);

  /**
   * @brief Comparison(==) operator overload. Case-sensitive.
   *
   * @param[in] str  constant ref to a CFX_ByteStringC object.
   *
   * @return <b>true</b> means equal, while <b>false</b> means not equal.
   */
  bool      operator == (const CFX_WideStringC& str) const
  {
    return   str.m_Length == m_Length && FXSYS_memcmp32(str.m_Ptr, m_Ptr, m_Length*sizeof(FX_WCHAR)) == 0;
  }
  /**
   * @brief Comparison(!=) operator overload. Case-sensitive.
   *
   * @param[in] str  constant ref to a CFX_WideStringC object.
   *
   * @return <b>true</b> means not equal, while <b>false</b> means equal.
   */
  bool      operator != (const CFX_WideStringC& str) const
  {
    return   str.m_Length != m_Length || FXSYS_memcmp32(str.m_Ptr, m_Ptr, m_Length*sizeof(FX_WCHAR)) != 0;
  }

  /**
   * @brief Get a constant wide string pointer to the wide string.
   *
   * @return A constant wide string pointer to the wide string.
   */
  FX_LPCWSTR    GetPtr() const { return m_Ptr; }
  /**
   * @brief Get the length of the byte string.
   *
   * @return The length of the byte string.
   */
  FX_STRSIZE    GetLength() const { return m_Length; }
  /**
   * @brief Determines whether current string object is empty.
   *
   * @return <b>true</b> means current string object is empty, while <b>false</b> means not.
   */
  bool      IsEmpty() const { return m_Length == 0; }

  /**
   * @brief Retrieves a single byte specified by an index number.
   *
   * @param[in] index  Specifies the zero-based index in the byte string.
   *
   * @return A single byte.
   */
  FX_WCHAR    GetAt(FX_STRSIZE index) const { return m_Ptr[index]; }

  /**
   * @brief Extracts the first (leftmost) count wide characters from this CFX_WideStringC object as a sub-string.
   *
   * @param[in] count  The count of wide characters expected to extract for the sub-string.
   *
   * @return A CFX_WideStringC sub-string.
   */
  CFX_WideStringC  Left(FX_STRSIZE count) const
  {
    if (count < 1) return CFX_WideStringC();
    if (count > m_Length) count = m_Length;
    return CFX_WideStringC(m_Ptr, count);
  }

  /**
   * @brief Extracts a substring of length count bytes from this CFX_WideStringC object, starting at position index (zero-based).
   *
   * @param[in] index  Specifies the zero-based index in the CFX_WideStringC object.
   * @param[in] count  Specifies the number of bytes to extract from this CFX_WideStringC object.
   *
   * @return A CFX_WideStringC object refer to the substring.
   */
  CFX_WideStringC  Mid(FX_STRSIZE index, FX_STRSIZE count = -1) const
  {
    if (index < 0) index = 0;
    if (index > m_Length) return CFX_WideStringC();
    if (count < 0 || count > m_Length - index) count = m_Length - index;
    return CFX_WideStringC(m_Ptr + index, count);
  }

  /**
   * @brief Extracts the last (rightmost) count wide characters from this CFX_WideStringC object as a sub-string.
   *
   * @param[in] count  The count of wide characters expected to extract for the sub-string.
   *
   * @return A CFX_WideStringC sub-string.
   */
  CFX_WideStringC  Right(FX_STRSIZE count) const
  {
    if (count < 1) return CFX_WideStringC();
    if (count > m_Length) count = m_Length;
    return CFX_WideStringC(m_Ptr + m_Length - count, count);
  }

 protected:
  /* The constant byte string pointer. */
  FX_LPCWSTR    m_Ptr;
  /* the length in bytes of the byte string. */
  FX_STRSIZE    m_Length;

 private:
  /*
   * new operator forbidden. Cannot allocate a CFX_WideStringC in heap.
   */
  void*      operator new (size_t) throw() { return NULL; }
};

/** @brief Type definition for a reference to a constant CFX_WideStringC object. */
typedef const CFX_WideStringC&  FX_WSTR;

/**
 * @brief All application should use the following macro when specifying a wide string constant.
 *        "wstr" must be a wide string constant.
 *
 * For example:
 * @code
 *    FX_WSTRC(L"abc").
 * @endcode
 */
#define FX_WSTRC(wstr) CFX_WideStringC((FX_LPCWSTR)wstr, sizeof(wstr) / sizeof(FX_WCHAR) - 1)

//*****************************************************************************
//* CFX_WideString - wide string
//*****************************************************************************
/** @brief This class represents the data of a wide string object. */
struct CFX_StringDataW
{
  /** @brief Reference count. */
  long    m_nRefs;
  /** @brief Length of data (excluding terminator). */
  FX_STRSIZE  m_nDataLength;
  /** @brief Length of allocation. */
  FX_STRSIZE  m_nAllocLength;
  /** @brief Real data (actually a variable-sized array). */
  FX_WCHAR  m_String[1];
};

/**
 * @brief WIDE STRING CLASS
 *
 * @details On Windows platforms, a wide string is represented by UTF-16LE encoding;
 *          On Unix/Linux platforms, a wide string is represented by UCS-4 encoding.
 */
class CFX_WideString : public CFX_Object
{
 public:
  /**
   * @brief Construct a null wide string.
   */
  CFX_WideString() { m_pData = NULL; }
  /**
   * @brief Copy constructor.
   *
   * @param[in] str  A constant ref to a CFX_WideString object.
   */
  CFX_WideString(const CFX_WideString& str);
  /**
   * @brief Construct from a wide character string.
   *
   * @param[in] ptr  Pointer to a constant wide character string.
   * @param[in] len  The length of the wide character string. This can be -1 for zero terminated wide character string.
   */
  CFX_WideString(FX_LPCWSTR ptr, FX_STRSIZE len = -1) { InitStr(ptr, len); }

  /**
   * @brief Construct from a single wide character.
   *
   * @param[in] ch  A single wide character.
   */
  CFX_WideString(FX_WCHAR ch);
  /**
   * @brief Construct from a constant ref to a CFX_WideStringC object.
   *
   * @param[in] str  A constant ref to a CFX_WideStringC object.
   */
  CFX_WideString(const CFX_WideStringC& str);
  /**
   * @brief Concatenate constructor.
   *
   * @param[in] str1  Fist constant ref to a CFX_WideStringC object.
   * @param[in] str2  Second constant ref to a CFX_WideStringC object.
   */
  CFX_WideString(const CFX_WideStringC& str1, const CFX_WideStringC& str2);
  /**
   * @brief The Destructor.
   */
  ~CFX_WideString();

  /**
   * @brief Create a wide string from system multi-byte charset.
   *
   * @param[in] str  a multi-byte charset string.
   * @param[in] len  The length in bytes of the multi-byte charset string.
   *                 This can be -1 for zero terminated multi-byte charset string.
   *
   * @return A wide string.
   */
  static CFX_WideString  FromLocal(const char* str, FX_STRSIZE len = -1);
  /**
   * @brief Create a wide string from UTF-8 string (ASCII string compatible).
   *
   * @param[in] str  A UTF8 string.
   * @param[in] len  The length in bytes of the UTF8 string. This can be -1 for zero terminated UTF8 string.
   *
   * @return A wide string.
   */
  static CFX_WideString  FromUTF8(const char* str, FX_STRSIZE len = -1);
  /**
   * @brief Create a wide string from UTF16LE encoded string.
   *
   * @param[in] str  A UTF16LE encoded string.
   * @param[in] len  The length in bytes of the UTF16LE encoded string. This can be -1 for zero terminated UTF16LE string.
   *
   * @return A wide string.
   */
  static CFX_WideString  FromUTF16LE(const unsigned short* str, FX_STRSIZE len = -1);

  /**
   * @brief Create a wide string from UTF16BE encoded string.
   *
   * @param[in] str  A UTF16BE encoded string.
   * @param[in] len  The length in bytes of the UTF16BE encoded string. This can be -1 for zero terminated UTF16BE string.
   *
   * @return A wide string.
   */
  static CFX_WideString  FromUTF16BE(const unsigned short* str, FX_STRSIZE len = -1);

  /**
   * @brief Length of string.
   *
   * @param[in] str  A string.
   *
   * @return The length of string.
   */
  static FX_STRSIZE       WStringLength(const unsigned short* str);

  /**
   * @brief FX_LPCWSTR type conversion operator.
   */
  operator FX_LPCWSTR() const { return m_pData ? m_pData->m_String : (FX_WCHAR*)L""; }

  /**
   * @brief Set this string to be empty.
   *
   * @return None.
   */
  void          Empty();
  /**
   * @brief Check whether current string object is empty.
   *
   * @return <b>true</b> means current string object is empty, while <b>false</b> means not.
   */
  FX_BOOL          IsEmpty() const { return !GetLength(); }

  /**
   * @brief Get number of characters, not bytes. Trailing zero not counted.
   *
   * @return The number of characters.
   */
  FX_STRSIZE        GetLength() const { return m_pData ? m_pData->m_nDataLength : 0; }

  /**
   * @brief Assignment(=) operator overload. From a wide character string.
   *
   * @param[in] str  The wide character string.
   *
   * @return A reference to current object itself.
   */
  const CFX_WideString&  operator = (FX_LPCWSTR str);

  /**
   * @brief Assignment(=) operator overload. From a wide string.
   *
   * @param[in] stringSrc  The Input wide string.
   *
   * @return A reference to current object itself.
   */
  const CFX_WideString&  operator =(const CFX_WideString& stringSrc);
  /**
   * @brief Assignment(=) operator overload. From a const wide string.
   *
   * @param[in] stringSrc  The Input wide string.
   *
   * @return A reference to current object itself.
   */
  const CFX_WideString&  operator =(const CFX_WideStringC& stringSrc);

  /**
   * @brief Concatenation(+=) operator overload. Concatenate a wide character string.
   *
   * @param[in] str  The wide character string.
   *
   * @return A reference to current object itself.
   */
  const CFX_WideString&  operator += (FX_LPCWSTR str);

  /**
   * @brief Concatenation(+=) operator overload. Concatenate a single wide character.
   *
   * @param[in] ch  The single wide character.
   *
   * @return A reference to current object itself.
   */
  const CFX_WideString&  operator += (FX_WCHAR ch);
  /**
   * @brief Concatenation(+=) operator overload. Concatenate a wide string.
   *
   * @param[in] str  The input wide string.
   *
   * @return A reference to current object itself.
   */
  const CFX_WideString&  operator += (const CFX_WideString& str);
  /**
   * @brief Concatenation(+=) operator overload. Concatenate a constant wide string.
   *
   * @param[in] str  The input wide string.
   *
   * @return A reference to current object itself.
   */
  const CFX_WideString&  operator += (const CFX_WideStringC& str);

  /**
   * @brief Retrieves a single wide character specified by an index number.
   *
   * @param[in] nIndex  Specifies the zero-based index in the wide string.
   *
   * @return A single wide character.
   */
  FX_WCHAR        GetAt(FX_STRSIZE nIndex) const { return m_pData ? m_pData->m_String[nIndex] : 0; }
  /**
   * @brief Subscript([]) operator overload. It retrieves a wide character specified by the zero-based index in nIndex.
   *
   * @param[in] nIndex  Specifies the zero-based index in the wide string.
   *
   * @return A single wide character.
   */
  FX_WCHAR        operator[](FX_STRSIZE nIndex) const { return m_pData ? m_pData->m_String[nIndex] : 0; }
  /**
   * @brief Overwrites a single wide character specified by an index number.
   *
   * @param[in] nIndex  Specifies the zero-based index in the wide string.
   * @param[in] ch      A single wide character.
   *
   * @return None.
   */
  void          SetAt(FX_STRSIZE nIndex, FX_WCHAR ch);

  /**
   * @brief Compare current string with a wide character string. Case-sensitive.
   *
   * @param[in] str  The wide character string to be compared.
   *
   * @return <ul>
   *         <li>-1 means current string is "smaller" (in alphabetic order) than the other one.</li>
   *         <li>0 means equal.</li>
   *         <li>1 means current string is "larger" (in alphabetic order) than the other one.</li>
   *         </ul>
   */
  int            Compare(FX_LPCWSTR str) const;
  /**
   * @brief Compare the the string with another. Case-sensitive.
   *
   * @param[in] str  The wide string to be compared.
   *
   * @return <ul>
   *         <li>-1 means current string is "smaller" (in alphabetic order) than the other one.</li>
   *         <li>0 means equal.</li>
   *         <li>1 means current string is "larger" (in alphabetic order) than the other one.</li>
   *         </ul>
   */
  int            Compare(const CFX_WideString& str) const;

  /**
   * @brief Compare the the string with a wide character string. No case-insensitive.
   *
   * @param[in] str  The wide character string to be compared.
   *
   * @return <ul>
   *         <li>-1 means current string is "smaller" (in alphabetic order) than the other one.</li>
   *         <li>0 means equal.</li>
   *         <li>1 means current string is "larger" (in alphabetic order) than the other one.</li>
   *         </ul>
   */
  int            CompareNoCase(FX_LPCWSTR str) const;

  /**
   * @brief Check if current string is equal to another.
   *
   * @details This function os faster than {@link CFX_WideString::Compare}when only need to
   *          check whether two strings are equal.
   *
   * @param[in] str  The wide string to be compared.
   *
   * @return <b>true</b> means equal, while <b>false</b> means not equal.
   */
  bool          Equal(const CFX_WideStringC& str) const;

  /**
   * @brief Extracts a substring from this CFX_WideString object, starting at position nFirst (zero-based) to last.
   *
   * @param[in] first  Specifies the zero-based index of the starting position in this CFX_WideString object.
   *
   * @return A CFX_WideString sub-string.
   */
  CFX_WideString      Mid(FX_STRSIZE first) const;
  /**
   * @brief Extracts a substring of count wide character from this CFX_WideString object,
   *        starting at position nFirst (zero-based) to last.
   *
   * @param[in] first  Specifies the zero-based index of the starting position in this CFX_WideString object.
   * @param[in] count  The count of wide characters expected to extract for the sub-string.
   *
   * @return A CFX_WideString sub-string.
   */
  CFX_WideString      Mid(FX_STRSIZE first, FX_STRSIZE count) const;
  /**
   * @brief Extracts the first (leftmost) count wide characters from this CFX_WideString object as a sub-string.
   *
   * @param[in] count  The count of wide characters expected to extract for the sub-string.
   *
   * @return A CFX_WideString sub-string.
   */
  CFX_WideString      Left(FX_STRSIZE count) const;
  /**
   * @brief Extracts the last (rightmost) count wide characters from this CFX_WideString object as a sub-string.
   *
   * @param[in] count  The count of wide characters expected to extract for the sub-string.
   *
   * @return A CFX_WideString sub-string.
   */
  CFX_WideString      Right(FX_STRSIZE count) const;

  /**
   * @brief Insert a wide character before specific position.
   *
   * @param[in] index  Specifies the zero-based index in the wide string.
   * @param[in] ch     A single wide character.
   *
   * @return The new length of the wide string.
   */
  FX_STRSIZE        Insert(FX_STRSIZE index, FX_WCHAR ch);
  /**
   * @brief Delete one or more wide characters starting from specific position.
   *
   * @param[in] index  Specifies the zero-based index in the wide string for starting deleting.
   * @param[in] count  Count of wide characters to be deleted.
   *
   * @return The new length of the wide string.
   */
  FX_STRSIZE        Delete(FX_STRSIZE index, FX_STRSIZE count = 1);
  /**
   * @brief Format a number of parameters into this wide string.
   *
   * @param[in] lpszFormat Specifies a format-control string.
   *
   * @return None.
   */
  void          Format(FX_LPCWSTR lpszFormat, ... );
  /**
   * @brief Format a number of parameters into this wide string. using va_list.
   *
   * @param[in] lpszFormat  Specifies a format-control string.
   * @param[in] argList     Variable-argument lists.
   *
   * @return None.
   *
   * @see CFX_WideString::Format
   */
  void          FormatV(FX_LPCWSTR lpszFormat, va_list argList);
  /**
   * @brief Change case of English letters to lower.
   *
   * @return None.
   */
  void          MakeLower();
  /**
   * @brief Change case of English letters to upper.
   *
   * @return None.
   */
  void          MakeUpper();

  /**
   * @brief Trim white spaces from the right side of the wide string.
   *
   * @return None.
   */
  void          TrimRight();
  /**
   * @brief Trim continuous occurrences of specified character from right side of the wide string.
   *
   * @param[in] chTarget  The specified character.
   *
   * @return None.
   */
  void          TrimRight(FX_WCHAR chTarget);
  /**
   * @brief Trim continuous occurrences of specified characters from right side of the wide string.
   *
   * @param[in] lpszTargets  The specified characters.
   *
   * @return None.
   */
  void          TrimRight(FX_LPCWSTR lpszTargets);

  /**
   * @brief Trim white spaces from the left side of the wide string.
   *
   * @return None.
   */
  void          TrimLeft();
  /**
   * @brief Trim continuous occurrences of specified character from left side of the wide string.
   *
   * @param[in] chTarget  The specified character.
   *
   * @return None.
   */
  void          TrimLeft(FX_WCHAR chTarget);
  /**
   * @brief Trim continuous occurrences of specified characters from left side of the wide string.
   *
   * @param[in] lpszTargets  The specified characters.
   *
   * @return None.
   */
  void          TrimLeft(FX_LPCWSTR lpszTargets);

  /**
   * @brief Reserve a buffer that can hold specific number of characters.
   *
   * @param[in] len  the Length expected to reserve.
   *
   * @return None.
   *
   * @see CFX_ByteString::Reserve(FX_STRSIZE)
   */
  void          Reserve(FX_STRSIZE len);
    /**
     * @brief Get a buffer with specific number of characters allocated.
     *
     * @param[in] len  the Length expected to get.
   *
     * @return A wide character string pointer to the wide string.
     */
  FX_LPWSTR        GetBuffer(FX_STRSIZE len);
  /**
   * @brief Lock and get the current string buffer, so the caller can modify the returned buffer.
   *        Caller can modified the returned buffer, and should call {@link CFX_WideString::ReleaseBuffer} after modification done.
   *
   * @return A wide character string pointer to the wide string.
   */
  FX_LPWSTR        LockBuffer();
  /**
   * @brief Release the buffer fetched by function {@link CFX_WideString::GetBuffer} or
   *        {@link CFX_WideString::LockBuffer}, and set the length of modified string.
   *
   * @param[in] len  Length expected to release to. -1 means that current string is assumed to be a zero-terminated string.
   *
   * @return None.
   */
  void          ReleaseBuffer(FX_STRSIZE len = -1);

  /**
   * @brief Convert to other data type.
   *
   * @return A decimal number.
   */
  int            GetInteger() const;

  /**
   * @brief Convert to other data type.
   *
   * @return A floating point number.
   */
  FX_FLOAT        GetFloat() const;

  /**
   * @brief Find a sub-string, from specific position. Only first occurrence is found.
   *
   * @param[in] lpszSub  The sub-string to be found.
   * @param[in] start    Specifies the zero-based index of the starting position to do finding. Default value: 0.
   *
   * @return The position of first occurrence in current string. -1 means not found.
   */
  FX_STRSIZE        Find(FX_LPCWSTR lpszSub, FX_STRSIZE start=0) const;
  /**
   * @brief Find a character, from specific position. Only first occurrence is found.
   *
   * @param[in] ch     The character to be found.
   * @param[in] start  Specifies the zero-based index of the starting position to do finding.Default value: 0.
   *
   * @return The position of first occurrence in current string. -1 means not found.
   */
  FX_STRSIZE        Find(FX_WCHAR ch, FX_STRSIZE start=0) const;

  /**
   * @brief Replace all patterns in the string with a new sub-string.
   *
   * @param[in] lpszOld  Specified the string to be matched and replaced in the wide string.
   * @param[in] lpszNew  Specified the string to replace.
   *
   * @return The number of replaced patterns.
   */
  FX_STRSIZE        Replace(FX_LPCWSTR lpszOld, FX_LPCWSTR lpszNew);
  /**
   * @brief Remove all occurrence of a particular character.
   *
   * @param[in] ch  Specified the character to be removed.
   *
   * @return The number of characters removed.
   */
  FX_STRSIZE        Remove(FX_WCHAR ch);

  /**
   * @brief Do UTF8 encoding.
   *
   * @return A byte string.
   */
  CFX_ByteString      UTF8Encode() const;
  /**
   * @brief Do UTF16LE encoding.
   *
   * @param[in] bTerminate
   *
   * @return A byte string which represents UTF-16LE encoded memory block.
   */
  CFX_ByteString      UTF16LE_Encode(FX_BOOL bTerminate = true) const;

  /**
   * @brief Load MBCS data into this wide string, using specified character mapper.
   *
   * @details If no character mapper specified, the system default mapper will be used.
   *
   * @param[in] str       A byte string.
   * @param[in] pCharMap  A character mapper.
   *
   * @return None.
   */
  void          ConvertFrom(const CFX_ByteString& str, CFX_CharMap* pCharMap = NULL);

 protected:
  void          InitStr(FX_LPCWSTR ptr, int len);

  /* Pointer to ref counted wide string data. */
  CFX_StringDataW*    m_pData;

  void          CopyBeforeWrite();
  void          AllocBeforeWrite(FX_STRSIZE nLen);

  void          ConcatInPlace(FX_STRSIZE nSrcLen, FX_LPCWSTR lpszSrcData);
  void          ConcatCopy(FX_STRSIZE nSrc1Len, FX_LPCWSTR lpszSrc1Data, FX_STRSIZE nSrc2Len, FX_LPCWSTR lpszSrc2Data);
  void          AssignCopy(FX_STRSIZE nSrcLen, FX_LPCWSTR lpszSrcData);
  void          AllocCopy(CFX_WideString& dest, FX_STRSIZE nCopyLen, FX_STRSIZE nCopyIndex, FX_STRSIZE nExtraLen) const;
};

inline CFX_WideStringC::CFX_WideStringC(const CFX_WideString& src)
{
  m_Ptr = (FX_LPCWSTR)src;
  m_Length = src.GetLength();
}

inline CFX_WideStringC& CFX_WideStringC::operator = (const CFX_WideString& src)
{
  m_Ptr = (FX_LPCWSTR)src;
  m_Length = src.GetLength();
  return *this;
}

/**
 * @name Wide string concatenation operation
 * 
 * @details Both side of the concatenation operator (+) can be:
 *          <ul>
 *          <li>A buffered wide string (const CFX_WideString&);</li>
 *          <li>A non-buffered wide string (const CFX_WideStringC&);</li>
 *          <li>A zero-terminated C-style wide string (FX_LPCWSTR);</li>
 *          <li>A single character (FX_WCHAR);</li>
 *          </ul>
 *          But you must have at least one CFX_WideString or CFX_WideStringC on one side.
 */
 /*@{*/

/**
 * @brief Concatenate a non-buffered wide string and a non-buffered wide string.
 *
 * @param[in] str1  A non-buffered wide string.
 * @param[in] str2  A non-buffered wide string.
 *
 * @return A CFX_WideString object.
 */
inline CFX_WideString operator + (const CFX_WideStringC& str1, const CFX_WideStringC& str2) { return CFX_WideString(str1, str2); }
#ifndef _NO_LPCSTR_SUPPORT_
/**
 * @brief Concatenate a non-buffered byte string and a zero-terminated C-style string
 *
 * @param[in] str1  A non-buffered wide string.
 * @param[in] str2  A zero-terminated C-style string.
 *
 * @return A CFX_WideString object.
 */
inline CFX_WideString operator + (const CFX_WideStringC& str1, FX_LPCWSTR str2) { return CFX_WideString(str1, str2); }
/**
 * @brief Concatenate a zero-terminated C-style string and a non-buffered byte string.
 *
 * @param[in] str1  A zero-terminated C-style string.
 * @param[in] str2  A non-buffered wide string.
 *
 * @return A CFX_WideString object.
 */
inline CFX_WideString operator + (FX_LPCWSTR str1,const CFX_WideStringC& str2) { return CFX_WideString(str1, str2); }
#endif
/**
 * @brief Concatenate a non-buffered byte string and a single character or byte.
 *
 * @param[in] str1  A non-buffered wide string.
 * @param[in] ch    A single character.
 *
 * @return A CFX_WideString object.
 */
inline CFX_WideString operator + (const CFX_WideStringC& str1, FX_WCHAR ch) { return CFX_WideString(str1, CFX_WideStringC(ch)); }
/**
 * @brief Concatenate a single character or byte and a non-buffered byte string.
 *
 * @param[in] ch    A single character.
 * @param[in] str2  A non-buffered wide string.
 *
 * @return A CFX_WideString object.
 */
inline CFX_WideString operator + (FX_WCHAR ch, const CFX_WideStringC& str2) { return CFX_WideString(ch, str2); }

/**
 * @brief Concatenate a buffered byte string and a buffered byte string.
 *
 * @param[in] str1  A buffered wide string.
 * @param[in] str2  A buffered wide string.
 *
 * @return A CFX_WideString object.
 */
inline CFX_WideString operator + (const CFX_WideString& str1, const CFX_WideString& str2) { return CFX_WideString(str1, str2); }
/**
 * @brief Concatenate a buffered byte string and a single character or byte.
 *
 * @param[in] str1  A buffered wide string.
 * @param[in] ch    A single character.
 *
 * @return A CFX_WideString object.
 */
inline CFX_WideString operator + (const CFX_WideString& str1, FX_WCHAR ch) { return CFX_WideString(str1, CFX_WideStringC(ch)); }
/**
 * @brief Concatenate a single character or byte and a buffered byte string.
 *
 * @param[in] ch    A single character.
 * @param[in] str2  A buffered wide string.
 *
 * @return A CFX_WideString object.
 */
inline CFX_WideString operator + (FX_WCHAR ch, const CFX_WideString& str2) { return CFX_WideString(ch, str2); }
#ifndef _NO_LPCSTR_SUPPORT_
/**
 * @brief Concatenate a buffered wide string and a zero-terminated C-style string.
 *
 * @param[in] str1  A buffered wide string.
 * @param[in] str2  A zero-terminated C-style string.
 *
 * @return A CFX_WideString object.
 */
inline CFX_WideString operator + (const CFX_WideString& str1, FX_LPCWSTR str2) { return CFX_WideString(str1, str2); }
/**
 * @brief Concatenate a zero-terminated C-style string and a buffered byte string.
 *
 * @param[in] str1  A zero-terminated C-style string.
 * @param[in] str2  A buffered wide string.
 *
 * @return A CFX_ByteString object.
 */
inline CFX_WideString operator + (FX_LPCWSTR str1, const CFX_WideString& str2) { return CFX_WideString(str1, str2); }
#endif
/**
 * @brief Concatenate a buffered byte string and a non-buffered byte string.
 *
 * @param[in] str1  A buffered wide string.
 * @param[in] str2  A non-buffered wide string.
 *
 * @return A CFX_WideString object.
 */
inline CFX_WideString operator + (const CFX_WideString& str1, const CFX_WideStringC& str2) { return CFX_WideString(str1, str2); }
/**
 * @brief Concatenate a non-buffered byte string and a buffered byte string.
 *
 * @param[in] str1  A non-buffered wide string.
 * @param[in] str2  A buffered wide string.
 *
 * @return A CFX_WideString object.
 */
inline CFX_WideString operator + (const CFX_WideStringC& str1, const CFX_WideString& str2) { return CFX_WideString(str1, str2); }

/*@}*/

/**
 * @name Wide string compare operation
 */
 /*@{*/

/**
 * @brief Comparison(==) operator overload. Case-sensitive.
 *
 * @param[in] s1  The first wide string.
 * @param[in] s2  The second wide string.
 *
 * @return <b>true</b> means equal, while <b>false</b> means not equal.
 */
bool operator==(const CFX_WideString& s1, const CFX_WideString& s2);
/**
 * @brief Comparison(==) operator overload. Case-sensitive.
 *
 * @param[in] s1  The first wide string.
 * @param[in] s2  The second wide string.
 *
 * @return <b>true</b> means equal, while <b>false</b> means not equal.
 */
bool operator==(const CFX_WideString& s1, const CFX_WideStringC& s2);
/**
 * @brief Comparison(==) operator overload. Case-sensitive.
 *
 * @param[in] s1  The first wide string.
 * @param[in] s2  The second wide string.
 *
 * @return <b>true</b> means equal, while <b>false</b> means not equal.
 */
bool operator==(const CFX_WideStringC& s1, const CFX_WideString& s2);
/**
 * @brief Comparison(==) operator overload. Case-sensitive.
 *
 * @param[in] s1  The first wide string.
 * @param[in] s2  The second wide character string.
 *
 * @return <b>true</b> means equal, while <b>false</b> means not equal.
 */
bool operator== (const CFX_WideString& s1, FX_LPCWSTR s2);
/**
 * @brief Comparison(==) operator overload. Case-sensitive.
 *
 * @param[in] s1  The first wide character string.
 * @param[in] s2  The second wide string.
 *
 * @return <b>true</b> means equal, while <b>false</b> means not equal.
 */
bool operator==(FX_LPCWSTR s1, const CFX_WideString& s2);

/**
 * @brief Comparison(!=) operator overload. Case-sensitive.
 *
 * @param[in] s1  The first wide string.
 * @param[in] s2  The second wide string.
 *
 * @return <b>true</b> means not equal, while <b>false</b> means equal.
 */
bool operator!=(const CFX_WideString& s1, const CFX_WideString& s2);
/**
 * @brief Comparison(!=) operator overload. Case-sensitive.
 *
 * @param[in] s1  The first wide string.
 * @param[in] s2  The second wide string.
 *
 * @return <b>true</b> means not equal, while <b>false</b> means equal.
 */
bool operator!=(const CFX_WideString& s1, const CFX_WideStringC& s2);
/**
 * @brief Comparison(!=) operator overload. Case-sensitive.
 *
 * @param[in] s1  The first wide string.
 * @param[in] s2  The second wide string.
 *
 * @return <b>true</b> means not equal, while <b>false</b> means equal.
 */
bool operator!=(const CFX_WideStringC& s1, const CFX_WideString& s2);
/**
 * @brief Comparison(!=) operator overload. Case-sensitive.
 *
 * @param[in] s1  The first wide string.
 * @param[in] s2  The second wide character string.
 *
 * @return <b>true</b> means not equal, while <b>false</b> means equal.
 */
bool operator!= (const CFX_WideString& s1, FX_LPCWSTR s2);
/**
 * @brief Comparison(!=) operator overload. Case-sensitive.
 *
 * @param[in] s1  The first wide character string.
 * @param[in] s2  The second wide string.
 *
 * @return <b>true</b> means not equal, while <b>false</b> means equal.
 */
bool operator!=(FX_LPCWSTR s1, const CFX_WideString& s2);

/**
 * @brief Comparison(<) operator overload. Case-sensitive.
 *
 * @param[in] lhs  The left hand side wide string.
 * @param[in] rhs  The right hand side wide string.
 *
 * @return <b>true</b> means lhs is smaller than rhs, while <b>false</b> means lhs is not smaller than rhs.
 */
bool operator< (const CFX_WideString& lhs, const CFX_WideString& rhs);

/*@}*/

/**
 *
 * @brief Convert a non-buffered byte string to a floating-point number.
 *
 * @param[in] str  A non-buffered byte string.
 *
 * @return A floating-point number.
 */
FX_FLOAT FX_atof(FX_BSTR str);
/**
 * @brief Convert a non-buffered byte string to a number.
 *
 * @param[in]  str        A non-buffered byte string.
 * @param[out] bInteger   Non-zero values means the string can convert to a number, otherwise can not.
 * @param[out] pData      It receives the converted number.
 * @param[in] sizeOfData  Size of pData. Default value: 4.
 *
 * @return None.
 */
void FX_atonum(FX_BSTR str, FX_BOOL& bInteger, void* pData, int sizeOfData = 4);

/**
 * @brief Convert float to byte string.
 *
 * @param[in] f     Float number.
 * @param[out] buf  Buffer of float string, buf should have 32 bytes at least.
 *
 * @return Length of formatted float string in buf, in bytes.
 */
FX_STRSIZE FX_ftoa(FX_FLOAT f, FX_LPSTR buf);

/**
 * @name Basic Unicode character attribute routines
 */
/*@{*/
/**
 * @brief Convert to upper-case letter.
 *
 * @param[in] wchar  A unicode character.
 *
 * @return The upper-case letter.
 */
FX_WCHAR  FXWCHAR_GetUpper(FX_WCHAR wchar);
/**
 * @brief Convert to lower-case letter.
 *
 * @param[in] wchar  A unicode character.
 *
 * @return The lower-case letter.
 */
FX_WCHAR  FXWCHAR_GetLower(FX_WCHAR wchar);
/**
 * @brief Check if the unicode can break a word.
 *
 * @param[in] wchar  A unicode character.
 *
 * @return <b>true</b> means the input unicode character can break a word,
 *         and <b>false</b> means the input unicode character cannot break a word.
 */
FX_BOOL    FXWCHAR_IsWordBreak(FX_WCHAR wchar);
/**
 * @brief Check if the unicode is space.
 *
 * @param[in] wchar  A unicode character.
 *
 * @return <b>true</b> means the input unicode character is space,
 *         and <b>false</b> means the input unicode character is not space.
 */
FX_BOOL    FXWCHAR_IsSpace(FX_WCHAR wchar);
/**
 * @name text direction defines
 */
/*@{*/
/** @brief Left to right order */
#define FXWCHAR_LTR      0
/** @brief Right to left order */
#define FXWCHAR_RTL      1
/** @brief Not sure about the order or don't care */
#define FXWCHAR_UNKNOWN    2
/*@}*/

/**
 * @brief Get text direction.
 *
 * @param[in] wchar  
 *
 * @return Direction value. Please refer to values starting from {@link ::FXWCHAR_LTR} and it would be one of these values.
 */
int      FXWCHAR_GetDirection(FX_WCHAR wchar);
/*@}*/
//<<<+++OPENSOURCE_END

/**
 * @name Encode wide string into UTF-8 byte string
 */
/*@{*/

/**
 * @brief Encode a wide string into a UTF-8 string.
 *
 * @param[in] pwsStr  Pointer to a wide string buffer.
 * @param[in] len     Length of wide string, in wide characters (FX_WCHAR).
 *
 * @return The object of encoded UTF-8 string.
 */
CFX_ByteString  FX_UTF8Encode(FX_LPCWSTR pwsStr, FX_STRSIZE len);
/**
 * @brief Encode a wide string into a UTF-8 string.
 *
 * @param[in] wsStr  A constant wide string.
 *
 * @return The object of encoded UTF-8 string.
 */
inline CFX_ByteString  FX_UTF8Encode(FX_WSTR wsStr) {return FX_UTF8Encode(wsStr.GetPtr(), wsStr.GetLength());}
/**
 * @brief Encode a wide string into a UTF-8 string.
 *
 * @param[in] wsStr  A wide string.
 *
 * @return The object of encoded UTF-8 string.
 */
inline CFX_ByteString  FX_UTF8Encode(const CFX_WideString &wsStr) {return FX_UTF8Encode((FX_LPCWSTR)wsStr, wsStr.GetLength());}

/**
 * @brief Determines if the arguments constitute UTF-16 surrogate pair.
 *
 * @param[in] first   First value of a UTF16 surrogate pair.
 * @param[in] second  Second value of a UTF16 surrogate pair.
 *
 * @return <b>true</b> means the arguments constitute UTF-16 surrogate pair
 *         and thus should be combined into a single Unicode code point.
 *
 * @note Only make sense if the the system uses UTF-16 for wide string encoding.
 *       All supported systems with 16 bit wchar_t (Windows, Cygwin, Symbian OS) do use UTF-16.
 */
inline FX_BOOL FX_IsUtf16SurrogatePair(FX_WCHAR first, FX_WCHAR second)
{
  return ((first & 0xFC00) == 0xD800 && (second & 0xFC00) == 0xDC00);
}

/**
 * @brief Creates a Unicode code point from UTF16 surrogate pair.
 * 
 * @param[in] first   First value of a UTF16 surrogate pair.
 * @param[in] second  Second value of a UTF16 surrogate pair.
 *
 * @return The Unicode code point.
 *
 * @note Only make sense if the the system uses UTF-16 for wide string encoding.
 *       All supported systems with 16 bit wchar_t (Windows, Cygwin, Symbian OS) do use UTF-16.
 */
inline FX_DWORD FX_CreateCodePointFromUtf16SurrogatePair(FX_WCHAR first,
  FX_WCHAR second)
{
  const FX_DWORD mask = (1 << 10) - 1;
  return  (((first & mask) << 10) | (second & mask)) + 0x10000;
  // This function should not be called when the condition is
  // false, but we provide a sensible default in case it is.
}

/*@}*/

//*****************************************************************************
//* CFX_ByteStringL - long term byte string
//*****************************************************************************
class CFX_ByteStringL : public CFX_ByteStringC
{
 public:
  CFX_ByteStringL() : CFX_ByteStringC() {}
  ~CFX_ByteStringL() {}

  void    Empty(IFX_Allocator* pAllocator);

  FX_LPSTR  AllocBuffer(FX_STRSIZE length, IFX_Allocator* pAllocator);

  void    Set(FX_BSTR src, IFX_Allocator* pAllocator);
};

//*****************************************************************************
//* CFX_WideStringL - long term wide string
//*****************************************************************************
class CFX_WideStringL : public CFX_WideStringC
{
 public:
  CFX_WideStringL() : CFX_WideStringC() {}
  ~CFX_WideStringL() {}

  void    Empty(IFX_Allocator* pAllocator);

  void    Set(FX_WSTR src, IFX_Allocator* pAllocator);

  int      GetInteger() const;
  FX_FLOAT  GetFloat() const;

  void    TrimRight(FX_LPCWSTR lpszTargets);
};

void  FX_UTF8Encode(FX_LPCWSTR pwsStr, FX_STRSIZE len, CFX_ByteStringL &utf8Str, IFX_Allocator* pAllocator = NULL);
//<<<+++OPENSOURCE_END

//<<<+++OPENSOURCE_MUST_BEGIN
#endif    // _FX_STRING_H_
//<<<+++OPENSOURCE_MUST_END

/** @} */

//<<<+++OPENSOURCE_END
