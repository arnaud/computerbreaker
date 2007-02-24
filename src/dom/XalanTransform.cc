/*
 * Copyright 1999-2004 The Apache Software Foundation.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <iostream>
#include <xercesc/util/PlatformUtils.hpp>
#include <xalanc/Include/PlatformDefinitions.hpp>
#include <xalanc/XalanTransformer/XalanTransformer.hpp>
#include "../util/Logger.hh"
#include "XalanTransform.hh"

int XalanTransform::transform(char *xml_filename, char *xsl_filename, char *out_filename) {
	XALAN_USING_STD(cerr)
	XALAN_USING_STD(cout)
	XALAN_USING_STD(endl)

	int	theResult = -1;

	try {
		XALAN_USING_XERCES(XMLPlatformUtils)

		XALAN_USING_XALAN(XalanTransformer)

		// Call the static initializer for Xerces.
		XMLPlatformUtils::Initialize();

		// Initialize Xalan.
		XalanTransformer::initialize();

		{
			// Create a XalanTransformer.
			XalanTransformer theXalanTransformer;

			// Do the transform.
			theResult = theXalanTransformer.transform(xml_filename, xsl_filename, out_filename);
    
			if(theResult != 0) {
				getLogger().error("XalanTransform : transform - '%s'", theXalanTransformer.getLastError());
			}
		}

		// Terminate Xalan...
		XalanTransformer::terminate();

		// Terminate Xerces...
		XMLPlatformUtils::Terminate();

		// Clean up the ICU, if it's integrated...
		XalanTransformer::ICUCleanUp();
	}
	catch(...) {
		getLogger().error("XalanTransform : transform - '%s'", "An unknown error occurred!");
	}

	return theResult;
}
