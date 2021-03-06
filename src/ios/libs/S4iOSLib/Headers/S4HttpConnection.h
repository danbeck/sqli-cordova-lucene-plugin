/* ***** BEGIN LICENSE BLOCK *****
 * Version: MPL 1.1
 *
 * The contents of this file are subject to the Mozilla Public License Version
 * 1.1 (the "License"); you may not use this file except in compliance with
 * the License. You may obtain a copy of the License at
 * http://www.mozilla.org/MPL/
 *
 * Software distributed under the License is distributed on an "AS IS" basis,
 * WITHOUT WARRANTY OF ANY KIND, either express or implied. See the License
 * for the specific language governing rights and limitations under the
 * License.
 *
 * The Original Code is the S4 iOS Libraries.
 *
 * The Initial Developer of the Original Code is
 * Michael Papp dba SeaStones Software Company.
 * All software created by the Initial Developer are Copyright (C) 2008-2012
 * the Initial Developer. All Rights Reserved.
 *
 * Original Author:
 *			Michael Papp, San Francisco, CA, USA
 *
 * ***** END LICENSE BLOCK ***** */

/* ***** FILE BLOCK ******
 *
 * Name:		S4HttpConnection.h
 * Module:		Network
 * Library:		S4 iOS Libraries
 *
 * ***** FILE BLOCK *****/


// ================================== Includes =========================================

#import <Foundation/Foundation.h>


// =================================== Defines =========================================



// ================================== Typedefs =========================================

typedef enum
{
	kCacheNoData			= 1,
	kWriteToFile			= 2,
	kCacheAllData			= 4
}	RequestedAction;


// ================================== Globals =========================================



// ============================= Forward Declarations =================================

@class S4HttpConnection;


// ================================== Protocols =======================================

@protocol S4HttpConnectionDelegate <NSObject>

@required
- (BOOL)httpConnection: (S4HttpConnection *)connection receivedData: (NSData *)data;
- (void)httpConnection: (S4HttpConnection *)connection failedWithError: (NSError *)error;
- (void)httpConnection: (S4HttpConnection *)connection completedWithData: (NSMutableData *)data;

@optional
//	Implement if the delegate wants to examine the HTTP response
- (BOOL)httpConnection: (S4HttpConnection *)connection receivedResponse: (NSURLResponse *)response;

//	Handle redirect requests
- (NSURLRequest *)httpConnection: (S4HttpConnection *)connection
		 receivedRedirectRequest: (NSURLRequest *)request
					 forResponse: (NSURLResponse *)redirectResponse;

//	Notifies delegate that new send stream is required for request
- (NSInputStream *)httpConnection: (S4HttpConnection *)connection
				needNewBodyStream: (NSURLRequest *)request;

//	Provides delegate with progress information for uploads
- (void)httpConnection: (S4HttpConnection *)connection
	 totalBytesWritten: (NSInteger)bytesWritten
	 totalBytesToWrite: (NSInteger)bytesToWrite;

//	Asks if the delegate can handle specific types of authentication
- (BOOL)httpConnection: (S4HttpConnection *)connection supportsProtectionSpace: (NSURLProtectionSpace *)protectionSpace;

//	Handle HTTPS authentication challenges
- (NSURLCredential *)httpConnection: (S4HttpConnection *)connection
			 respondToAuthChallenge: (NSURLAuthenticationChallenge *)challenge;

@end



// ============================== S4HttpConnection Class ==============================

@interface S4HttpConnection : NSObject <NSURLConnectionDataDelegate, NSURLConnectionDelegate>
{
}

- (BOOL)openConnectionForRequest: (NSURLRequest *)request delegate: (NSObject <S4HttpConnectionDelegate> *)delegate;
- (BOOL)openNonCachingConnectionForRequest: (NSURLRequest *)request delegate: (NSObject <S4HttpConnectionDelegate> *)delegate;
- (BOOL)openConnectionForRequest: (NSURLRequest *)request
						delegate: (NSObject <S4HttpConnectionDelegate> *)delegate
			   writeToFileAtPath: (NSString *)path
						withName: (NSString *)fileName
					  useTmpFile: (BOOL)bUseTmpFile;
- (void)cancelConnection;

// NSURLConnectionDataDelegate delegate methods
- (void)connection: (NSURLConnection *)connection didReceiveResponse: (NSURLResponse *)response;
- (void)connection: (NSURLConnection *)connection didReceiveData: (NSData *)data;
- (NSURLRequest *)connection: (NSURLConnection *)connection willSendRequest: (NSURLRequest *)request redirectResponse: (NSURLResponse *)response;
- (NSCachedURLResponse *)connection: (NSURLConnection *)connection willCacheResponse: (NSCachedURLResponse *)cachedResponse;
- (NSInputStream *)connection: (NSURLConnection *)connection needNewBodyStream: (NSURLRequest *)request;
- (void)connection: (NSURLConnection *)connection didSendBodyData: (NSInteger)bytesWritten
												totalBytesWritten: (NSInteger)totalBytesWritten
										totalBytesExpectedToWrite: (NSInteger)totalBytesExpectedToWrite;
- (void)connectionDidFinishLoading: (NSURLConnection *)connection;

// NSURLConnectionDelegate delegate methods
- (void)connection: (NSURLConnection *)connection didFailWithError: (NSError *)error;
- (BOOL)connection: (NSURLConnection *)connection canAuthenticateAgainstProtectionSpace: (NSURLProtectionSpace *)protectionSpace;
- (void)connection: (NSURLConnection *)connection didReceiveAuthenticationChallenge: (NSURLAuthenticationChallenge *)challenge;

@end
