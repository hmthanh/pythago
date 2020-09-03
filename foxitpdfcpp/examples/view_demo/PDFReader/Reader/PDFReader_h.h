

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 7.00.0555 */
/* at Thu Sep 14 08:59:27 2017
 */
/* Compiler settings for PDFReader.idl:
    Oicf, W1, Zp8, env=Win32 (32b run), target_arch=X86 7.00.0555 
    protocol : dce , ms_ext, c_ext, robust
    error checks: allocation ref bounds_check enum stub_data 
    VC __declspec() decoration level: 
         __declspec(uuid()), __declspec(selectany), __declspec(novtable)
         DECLSPEC_UUID(), MIDL_INTERFACE()
*/
/* @@MIDL_FILE_HEADING(  ) */

#pragma warning( disable: 4049 )  /* more than 64k source lines */


/* verify that the <rpcndr.h> version is high enough to compile this file*/
#ifndef __REQUIRED_RPCNDR_H_VERSION__
#define __REQUIRED_RPCNDR_H_VERSION__ 475
#endif

#include "rpc.h"
#include "rpcndr.h"

#ifndef __RPCNDR_H_VERSION__
#error this stub requires an updated version of <rpcndr.h>
#endif // __RPCNDR_H_VERSION__


#ifndef __PDFReader_h_h__
#define __PDFReader_h_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef __IPDFReader_FWD_DEFINED__
#define __IPDFReader_FWD_DEFINED__
typedef interface IPDFReader IPDFReader;
#endif   /* __IPDFReader_FWD_DEFINED__ */


#ifndef __CPDFReaderDoc_FWD_DEFINED__
#define __CPDFReaderDoc_FWD_DEFINED__

#ifdef __cplusplus
typedef class CPDFReaderDoc CPDFReaderDoc;
#else
typedef struct CPDFReaderDoc CPDFReaderDoc;
#endif /* __cplusplus */

#endif   /* __CPDFReaderDoc_FWD_DEFINED__ */


#ifdef __cplusplus
extern "C"{
#endif 



#ifndef __PDFReader_LIBRARY_DEFINED__
#define __PDFReader_LIBRARY_DEFINED__

/* library PDFReader */
/* [version][uuid] */ 


EXTERN_C const IID LIBID_PDFReader;

#ifndef __IPDFReader_DISPINTERFACE_DEFINED__
#define __IPDFReader_DISPINTERFACE_DEFINED__

/* dispinterface IPDFReader */
/* [uuid] */ 


EXTERN_C const IID DIID_IPDFReader;

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("935093B6-4FDF-4236-B098-0BFC28678E81")
    IPDFReader : public IDispatch
    {
    };
    
#else   /* C style interface */

    typedef struct IPDFReaderVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IPDFReader * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IPDFReader * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IPDFReader * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IPDFReader * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IPDFReader * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IPDFReader * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IPDFReader * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        END_INTERFACE
    } IPDFReaderVtbl;

    interface IPDFReader
    {
        CONST_VTBL struct IPDFReaderVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IPDFReader_QueryInterface(This,riid,ppvObject)  \
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IPDFReader_AddRef(This)  \
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IPDFReader_Release(This)  \
    ( (This)->lpVtbl -> Release(This) ) 


#define IPDFReader_GetTypeInfoCount(This,pctinfo)  \
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define IPDFReader_GetTypeInfo(This,iTInfo,lcid,ppTInfo)  \
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define IPDFReader_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)  \
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define IPDFReader_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)  \
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 

#endif /* COBJMACROS */


#endif   /* C style interface */


#endif   /* __IPDFReader_DISPINTERFACE_DEFINED__ */


EXTERN_C const CLSID CLSID_CPDFReaderDoc;

#ifdef __cplusplus

class DECLSPEC_UUID("1B686C72-D3E5-4B41-988F-2055D7088280")
CPDFReaderDoc;
#endif
#endif /* __PDFReader_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


