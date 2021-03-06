/*
 * BaseDataID.h
 *
 *ã?ªã¼ãã?ã©ã¤ãããªã?ã¨
 * 
 *  Copyright(c) Live2D Inc. All rights reserved.
 *  [[ CONFIDENTIAL ]]
 */
#ifndef __LIVE2D_BASE_DATA_ID_H__
#define __LIVE2D_BASE_DATA_ID_H__


#include "../Live2D.h"
#include "../type/LDVector.h"
#include "ID.h"

//------------ LIVE2D NAMESPACE ------------
namespace live2d
{
	
	class BaseDataID : public ID
	{
	public:
		const static int L2D_BASEDATA_ID_INITIAL_CAPACITY = 128 ;
	
	public:
	
		// IDãåå¾ãã?
		// ã»åä¸??å¤ãæã¤å¨ã¦ã®IDãã?åããã¤ã³ã¿ãæããã¨ãä¿è¨¼ãã ?åä¸??ç¢ºèªãã?= æ¯è¼?ã§è¯ã?¼?\n
		// ã»Live2D::dispose()æã«è§£æ¾ããã?
		static BaseDataID * getID(const live2d::LDString &str ) ;
	
		static BaseDataID * getID(  const RefString& refStr ) ;
	
		static BaseDataID * DST_BASE_ID()
		{
			if( dstBaseId == NULL )
			{
				dstBaseId = getID("DST_BASE");
			}
			return dstBaseId ;
		}
	
		
		// ãªãªã¼ã¹ç¨ã¡ã½ã???ive2D::diposeããå¼ã°ãã)
		static void releaseStored_notForClientCall() ;
	
	public:
		
		const char * toChar(){ return id.c_str() ; }
		
	private:	
		BaseDataID() ;									
		BaseDataID(const live2d::LDString &str );		
		BaseDataID( const char* str ) ;					
		BaseDataID( const RefString& refStr ) ;			
	
		//Prevention of copy Constructor
		BaseDataID( const BaseDataID & ) ;				
		BaseDataID& operator=( const BaseDataID & ) ; 	
	
	
		virtual ~BaseDataID();
		
	private:
		static LDVector<BaseDataID*>* 		idlist_BaseDataID ;
		static BaseDataID * 				dstBaseId ;
		
	private:
		live2d::LDString 					id ;				// çæ?æã«è¤?£½ããã¦ã?ãããDestructorã§éæ¾ãã
	};
	
}

#endif		// __LIVE2D_BASE_DATA_ID_H__
//------------ LIVE2D NAMESPACE ------------

