/*
 This file is part of the Computer Breaker project.

    Computer Breaker is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    Computer Breaker is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with Computer Breaker; if not, write to the Free Software
    Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/

#include "XPathQueryManager.hh"

#include <xercesc/util/PlatformUtils.hpp>
#include <xercesc/framework/LocalFileInputSource.hpp>

#include <xalanc/Include/PlatformDefinitions.hpp>
#include <xalanc/XPath/XPathEvaluator.hpp>
#include <xalanc/XPath/XObject.hpp>
#include <xalanc/PlatformSupport/XSLException.hpp>
#include <xalanc/DOMSupport/XalanDocumentPrefixResolver.hpp>

#include <xalanc/XalanSourceTree/XalanSourceTreeDOMSupport.hpp>
#include <xalanc/XalanSourceTree/XalanSourceTreeParserLiaison.hpp>
#include <xalanc/XalanDOM/XalanEmptyNamedNodeMap.hpp>
#include <xalanc/XalanDOM/XalanNodeListDummy.hpp>


#include <iostream>
#include <vector>

#include "../util/Logger.hh"

XALAN_USING_XERCES(XMLPlatformUtils)
XALAN_USING_XALAN(XPathEvaluator)
XALAN_USING_XALAN(XalanNode)


XPathQueryManager::XPathQueryManager(std::string file_name) {
	_file_name = file_name;
}


const std::string XPathQueryManager::getXpathResultString(const std::string xPathQuery, const std::string contextNode){
	
	getLogger().debug("XPathQueryManager : getXpathResultString() - begin");

	std::string output;
		
	XALAN_USING_XALAN(XSLException)

    try {
		XALAN_USING_XERCES(XMLPlatformUtils)
		XALAN_USING_XALAN(XPathEvaluator)

		XMLPlatformUtils::Initialize();
		XPathEvaluator::initialize();

		{
			XALAN_USING_XERCES(LocalFileInputSource)
			XALAN_USING_XALAN(XalanDocument)
			XALAN_USING_XALAN(XalanDocumentPrefixResolver)
			XALAN_USING_XALAN(XalanDOMString)
			XALAN_USING_XALAN(XalanNode)
			XALAN_USING_XALAN(XalanSourceTreeDOMSupport)
			XALAN_USING_XALAN(XalanSourceTreeParserLiaison)
			XALAN_USING_XALAN(XObjectPtr)

			// We'll use these to parse the XML file.
			XalanSourceTreeDOMSupport theDOMSupport;
			XalanSourceTreeParserLiaison theLiaison(theDOMSupport);

			// Hook the two together...
			theDOMSupport.setParserLiaison(&theLiaison);

			const XalanDOMString theFileName(_file_name.c_str());

			// Create an input source that represents a local file...
			const LocalFileInputSource theInputSource(theFileName.c_str());

			// Parse the document...
			XalanDocument* const theDocument = theLiaison.parseXMLStream(theInputSource);
			assert(theDocument != 0);

			XalanDocumentPrefixResolver	thePrefixResolver(theDocument);

			XPathEvaluator theEvaluator;

			// OK, let's find the context node...
			XalanNode* const theContextNode =
					theEvaluator.selectSingleNode(
						theDOMSupport,
						theDocument,
						XalanDOMString(contextNode.c_str()).c_str(),
						thePrefixResolver);

			if (theContextNode == 0) {
				getLogger().warn("XPathQueryManager : getXpathResultString() - No nodes matched the location path");
			} else {
				// OK, let's evaluate the expression...
				const XObjectPtr theResult(
					theEvaluator.evaluate(
							theDOMSupport,
							theContextNode,
							XalanDOMString(xPathQuery.c_str()).c_str(),
							thePrefixResolver));

				assert(theResult.null() == false);
				
				output = convertToString(theResult->str());
			}
		}
		XPathEvaluator::terminate();
		XMLPlatformUtils::Terminate();
	}
    catch(const XSLException& theException) {
    	getLogger().error("XPathQueryManager : getXpathResultString() - XSL exception");
		return "";
    }
	catch(...) {
		getLogger().error("XPathQueryManager : getXpathResultString() - Generic exception caught!");
		return "";
	}
	
	getLogger().debug("XPathQueryManager : getXpathResultString() - end");
	return output;
}

/**
 * fonction qui concatène les différentes valeurs des noeuds texte.
 */
const std::string XPathQueryManager::getXpathResultStringMultiple(const std::string xPathQuery, const std::string contextNode){
	
	getLogger().debug("XPathQueryManager : getXpathResultStringMultiple() - begin");

	std::string output = "";
		
	XALAN_USING_XALAN(XSLException)

    try {
		XALAN_USING_XERCES(XMLPlatformUtils)
		XALAN_USING_XALAN(XPathEvaluator)

		XMLPlatformUtils::Initialize();
		XPathEvaluator::initialize();

		{
			XALAN_USING_XERCES(LocalFileInputSource)
			XALAN_USING_XALAN(XalanDocument)
			XALAN_USING_XALAN(XalanDocumentPrefixResolver)
			XALAN_USING_XALAN(XalanDOMString)
			XALAN_USING_XALAN(XalanNode)
			XALAN_USING_XALAN(XalanSourceTreeDOMSupport)
			XALAN_USING_XALAN(XalanSourceTreeParserLiaison)
			XALAN_USING_XALAN(XObjectPtr)

			// We'll use these to parse the XML file.
			XalanSourceTreeDOMSupport theDOMSupport;
			XalanSourceTreeParserLiaison theLiaison(theDOMSupport);

			// Hook the two together...
			theDOMSupport.setParserLiaison(&theLiaison);

			const XalanDOMString theFileName(_file_name.c_str());

			// Create an input source that represents a local file...
			const LocalFileInputSource theInputSource(theFileName.c_str());

			// Parse the document...
			XalanDocument* const theDocument = theLiaison.parseXMLStream(theInputSource);
			assert(theDocument != 0);

			XalanDocumentPrefixResolver	thePrefixResolver(theDocument);

			XPathEvaluator theEvaluator;

			// OK, let's find the context node...
			XalanNode* const theContextNode =
					theEvaluator.selectSingleNode(
						theDOMSupport,
						theDocument,
						XalanDOMString(contextNode.c_str()).c_str(),
						thePrefixResolver);

			if (theContextNode == 0) {
				getLogger().warn("XPathQueryManager : getXpathResultStringMultiple() - No nodes matched the location path");
			} else {
				// OK, let's evaluate the expression...
				const XObjectPtr theResult(
					theEvaluator.evaluate(
							theDOMSupport,
							theContextNode,
							XalanDOMString(xPathQuery.c_str()).c_str(),
							thePrefixResolver));

				assert(theResult.null() == false);
				
				const XALAN_CPP_NAMESPACE::NodeRefListBase& nodeset = theResult->nodeset();
				
				for (unsigned int i=0; i<nodeset.getLength(); i++){
					XalanNode *node = (XalanNode *)nodeset.item(i);
					output += convertToString(node->getNodeValue());
					if (i != nodeset.getLength()-1)
						output += " ,";
				}

			}
		}
		XPathEvaluator::terminate();
		XMLPlatformUtils::Terminate();
	}
    catch(const XSLException& theException) {
    	getLogger().error("XPathQueryManager : getXpathResultStringMultiple() - XSL exception");
		return "";
    }
	catch(...) {
		getLogger().error("XPathQueryManager : getXpathResultStringMultiple() - Generic exception caught!");
		return "";
	}
	
	getLogger().debug("XPathQueryManager : getXpathResultStringMultiple() - end");
	return output;
}



double XPathQueryManager::getXpathResultDouble(const std::string xPathQuery, const std::string contextNode){
	
	getLogger().debug("XPathQueryManager : getXpathResultDouble() - begin");

	double output = 0;
		
	XALAN_USING_XALAN(XSLException)

    try {
		XALAN_USING_XERCES(XMLPlatformUtils)
		XALAN_USING_XALAN(XPathEvaluator)

		XMLPlatformUtils::Initialize();
		XPathEvaluator::initialize();

		{
			XALAN_USING_XERCES(LocalFileInputSource)
			XALAN_USING_XALAN(XalanDocument)
			XALAN_USING_XALAN(XalanDocumentPrefixResolver)
			XALAN_USING_XALAN(XalanDOMString)
			XALAN_USING_XALAN(XalanNode)
			XALAN_USING_XALAN(XalanSourceTreeDOMSupport)
			XALAN_USING_XALAN(XalanSourceTreeParserLiaison)
			XALAN_USING_XALAN(XObjectPtr)

			// We'll use these to parse the XML file.
			XalanSourceTreeDOMSupport theDOMSupport;
			XalanSourceTreeParserLiaison theLiaison(theDOMSupport);

			// Hook the two together...
			theDOMSupport.setParserLiaison(&theLiaison);

			const XalanDOMString theFileName(_file_name.c_str());

			// Create an input source that represents a local file...
			const LocalFileInputSource theInputSource(theFileName.c_str());

			// Parse the document...
			XalanDocument* const theDocument = theLiaison.parseXMLStream(theInputSource);
			assert(theDocument != 0);

			XalanDocumentPrefixResolver	thePrefixResolver(theDocument);

			XPathEvaluator theEvaluator;

			// OK, let's find the context node...
			XalanNode* const theContextNode =
					theEvaluator.selectSingleNode(
						theDOMSupport,
						theDocument,
						XalanDOMString(contextNode.c_str()).c_str(),
						thePrefixResolver);

			if (theContextNode == 0) {
				getLogger().warn("XPathQueryManager : getXpathResultDouble() - No nodes matched the location path");
			} else {
				// OK, let's evaluate the expression...
				const XObjectPtr theResult(
					theEvaluator.evaluate(
							theDOMSupport,
							theContextNode,
							XalanDOMString(xPathQuery.c_str()).c_str(),
							thePrefixResolver));

				assert(theResult.null() == false);
				
				output = theResult->num();
			}
		}
		XPathEvaluator::terminate();
		XMLPlatformUtils::Terminate();
	}
    catch(const XSLException& theException) {
    	getLogger().error("XPathQueryManager : getXpathResultDouble() - XSL exception");
		return -1;
    }
	catch(...) {
		getLogger().error("XPathQueryManager : getXpathResultDouble() - Generic exception caught!");
		return -1;
	}
	
	getLogger().debug("XPathQueryManager : getXpathResultDouble() - end");
	return output;
}


TCollection<Service*> *XPathQueryManager::getXpathResultServices(const std::string xPathQuery, const std::string contextNode){
	
	getLogger().debug("XPathQueryManager : getXpathResultServices() - begin");

	//const XALAN_CPP_NAMESPACE::NodeRefListBase *output = 0;
	TCollection<Service*> *output = new TCollection<Service*>();
		
	XALAN_USING_XALAN(XSLException)

    try {
		XALAN_USING_XERCES(XMLPlatformUtils)
		XALAN_USING_XALAN(XPathEvaluator)

		XMLPlatformUtils::Initialize();
		XPathEvaluator::initialize();

		{
			XALAN_USING_XERCES(LocalFileInputSource)
			XALAN_USING_XALAN(XalanDocument)
			XALAN_USING_XALAN(XalanDocumentPrefixResolver)
			XALAN_USING_XALAN(XalanDOMString)
			XALAN_USING_XALAN(XalanNode)
			XALAN_USING_XALAN(XalanEmptyNamedNodeMap)
			XALAN_USING_XALAN(XalanSourceTreeDOMSupport)
			XALAN_USING_XALAN(XalanSourceTreeParserLiaison)
			XALAN_USING_XALAN(XObjectPtr)
			XALAN_USING_XALAN(XalanNodeListDummy)
			XALAN_USING_XALAN(XalanElement)

			// We'll use these to parse the XML file.
			XalanSourceTreeDOMSupport theDOMSupport;
			XalanSourceTreeParserLiaison theLiaison(theDOMSupport);

			// Hook the two together...
			theDOMSupport.setParserLiaison(&theLiaison);

			const XalanDOMString theFileName(_file_name.c_str());

			// Create an input source that represents a local file...
			const LocalFileInputSource theInputSource(theFileName.c_str());

			// Parse the document...
			XalanDocument* const theDocument = theLiaison.parseXMLStream(theInputSource);
			assert(theDocument != 0);

			XalanDocumentPrefixResolver	thePrefixResolver(theDocument);

			XPathEvaluator theEvaluator;

			// OK, let's find the context node...
			XalanNode* const theContextNode =
					theEvaluator.selectSingleNode(
						theDOMSupport,
						theDocument,
						XalanDOMString(contextNode.c_str()).c_str(),
						thePrefixResolver);

			if (theContextNode == 0) {
				getLogger().warn("XPathQueryManager : getXpathResultServices() - No nodes matched the location path");
			} else {
				// OK, let's evaluate the expression...
				const XObjectPtr theResult(
					theEvaluator.evaluate(
							theDOMSupport,
							theContextNode,
							XalanDOMString(xPathQuery.c_str()).c_str(),
							thePrefixResolver));

				assert(theResult.null() == false);
				
				const XALAN_CPP_NAMESPACE::NodeRefListBase& nodeset = theResult->nodeset();
				
				for (unsigned int i=0; i<nodeset.getLength(); i++){
					Service *service = new Service();
					XalanNode *nodePort = (XalanNode *)nodeset.item(i);
					
					XalanNode *childService = getNodeChild(nodePort, "service");
					std::string serviceName = getAttributeByName(childService, "name");
					service->setName(serviceName.c_str());					

					std::string numport = getAttributeByName(nodePort, "portid");
					service->setPort(atoi(numport.c_str()));
					
					std::string protocol = getAttributeByName(nodePort, "protocol");
					service->setProtocol(protocol);
					
					
					TCollection<Vulnerability*> *vulns = new TCollection<Vulnerability*>();
					/* on recupere les informations pour les vulnérabilités */
					XalanNode *nodeInfo = nodePort->getFirstChild();
					while(nodeInfo != 0){
						if (nodeInfo->getNodeName() == (XalanDOMString)"information"){
							Vulnerability *vuln = new Vulnerability();
							
							XalanNode *tmpNode = getNodeChild(nodeInfo, "id");
							std::string tmpString = convertToString(tmpNode->getFirstChild()->getNodeValue());
							vuln->setId(tmpString.c_str());
							
							tmpNode = getNodeChild(nodeInfo, "bugtraq_id");
							tmpString = "";
							if (tmpNode->getFirstChild() != 0)
								tmpString = convertToString(tmpNode->getFirstChild()->getNodeValue());
							vuln->setBugtrackId(tmpString.c_str());
							
							tmpNode = getNodeChild(nodeInfo, "cve_id");
							tmpString = "";
							if (tmpNode->getFirstChild() != 0)
								tmpString = convertToString(tmpNode->getFirstChild()->getNodeValue());
							vuln->setCveId(tmpString.c_str());
							
							vulns->add(vuln);
						}
						nodeInfo = nodeInfo->getNextSibling();
					}
					service->setVulnerabilities(vulns);

					output->add(service);
				}
			}
		}
		XPathEvaluator::terminate();
		XMLPlatformUtils::Terminate();
	}
    catch(const XSLException& theException) {
    	getLogger().error("XPathQueryManager : getXpathResultServices() - XSL exception");
		return 0;
    }
	catch(...) {
		getLogger().error("XPathQueryManager : getXpathResultServices() - Generic exception caught!");
		return 0;
	}
	
	getLogger().debug("XPathQueryManager : getXpathResultServices() - end");
	return output;
}


XalanNode *XPathQueryManager::getNodeChild(const XalanNode *parentNode, const std::string name) {
	XALAN_USING_XALAN(XalanDOMString)
	if (!parentNode->hasChildNodes()){
		return 0;
	}
	
	XalanNode *node = parentNode->getFirstChild();
	while((node != 0) && (node->getNodeName() != (XalanDOMString)name.c_str()) ) {
		node = node->getNextSibling();
	}
	return node;
}


std::string XPathQueryManager::getAttributeByName(const XalanNode *node, const std::string attributeName) {
	XALAN_USING_XALAN(XalanEmptyNamedNodeMap)
	XALAN_USING_XALAN(XalanDOMString)
	
	const XalanEmptyNamedNodeMap *attributes = (XalanEmptyNamedNodeMap *) node->getAttributes();
	XalanNode *nodeReturn = attributes->getNamedItem((XalanDOMString)attributeName.c_str());
	
	return convertToString(nodeReturn->getNodeValue());
	
}


std::string XPathQueryManager::convertToString(const XALAN_CPP_NAMESPACE::XalanDOMString xalanString) {
	if (xalanString.size() != 0){
	  	XALAN_CPP_NAMESPACE::CharVectorType  my_target_vector;
		XALAN_CPP_NAMESPACE::TranscodeToLocalCodePage( xalanString, my_target_vector, false);
		
		std::string result = &*my_target_vector.begin();
		result[my_target_vector.size()] = '\0';
		return result;
	}
	return "";
}


/**
 * recupere les vulnerabilités pour un service donné.
 * 
 */
TCollection<Vulnerability*> *XPathQueryManager::getXpathResultVulnerabilities(const std::string xPathQuery, const std::string contextNode){
	
	getLogger().debug("XPathQueryManager : getXpathResultVulnerabilities() - begin");
	
	TCollection<Vulnerability*> *output = new TCollection<Vulnerability*>();
	
	XALAN_USING_XALAN(XSLException)

    try {
		XALAN_USING_XERCES(XMLPlatformUtils)
		XALAN_USING_XALAN(XPathEvaluator)

		XMLPlatformUtils::Initialize();
		XPathEvaluator::initialize();

		{
			XALAN_USING_XERCES(LocalFileInputSource)
			XALAN_USING_XALAN(XalanDocument)
			XALAN_USING_XALAN(XalanDocumentPrefixResolver)
			XALAN_USING_XALAN(XalanDOMString)
			XALAN_USING_XALAN(XalanNode)
			XALAN_USING_XALAN(XalanEmptyNamedNodeMap)
			XALAN_USING_XALAN(XalanSourceTreeDOMSupport)
			XALAN_USING_XALAN(XalanSourceTreeParserLiaison)
			XALAN_USING_XALAN(XObjectPtr)
			XALAN_USING_XALAN(XalanNodeListDummy)
			XALAN_USING_XALAN(XalanElement)

			// We'll use these to parse the XML file.
			XalanSourceTreeDOMSupport theDOMSupport;
			XalanSourceTreeParserLiaison theLiaison(theDOMSupport);

			// Hook the two together...
			theDOMSupport.setParserLiaison(&theLiaison);

			const XalanDOMString theFileName(_file_name.c_str());

			// Create an input source that represents a local file...
			const LocalFileInputSource theInputSource(theFileName.c_str());

			// Parse the document...
			XalanDocument* const theDocument = theLiaison.parseXMLStream(theInputSource);
			assert(theDocument != 0);

			XalanDocumentPrefixResolver	thePrefixResolver(theDocument);

			XPathEvaluator theEvaluator;

			// OK, let's find the context node...
			XalanNode* const theContextNode =
					theEvaluator.selectSingleNode(
						theDOMSupport,
						theDocument,
						XalanDOMString(contextNode.c_str()).c_str(),
						thePrefixResolver);

			if (theContextNode == 0) {
				getLogger().warn("XPathQueryManager : getXpathResultVulnerabilities() - No nodes matched the location path");
			} else {
				// OK, let's evaluate the expression...
				const XObjectPtr theResult(
					theEvaluator.evaluate(
							theDOMSupport,
							theContextNode,
							XalanDOMString(xPathQuery.c_str()).c_str(),
							thePrefixResolver));

				assert(theResult.null() == false);
				
				const XALAN_CPP_NAMESPACE::NodeRefListBase& nodeset = theResult->nodeset();
				
				
				for (unsigned int i=0; i<nodeset.getLength(); i++){
					Vulnerability *vuln = new Vulnerability();
					XalanNode *nodeService = (XalanNode *)nodeset.item(i);
					
					/* id */
					XalanNode *childVulnerability = getNodeChild(nodeService, "vulnerability");
					std::string tmpString = getAttributeByName(childVulnerability, "id");
					vuln->setId(tmpString.c_str());
					getLogger().warn("XPathQueryManager : getXpathResultVulnerabilities() - id: %s",tmpString.c_str());
					
					/* bugtrack id */
					XalanNode *nodeTmp = getNodeChild(childVulnerability, "id-bugtrack");
					tmpString = "";
					if (nodeTmp->getFirstChild() != 0)
						tmpString = convertToString(nodeTmp->getFirstChild()->getNodeValue());
					vuln->setBugtrackId(tmpString.c_str());
					getLogger().warn("XPathQueryManager : getXpathResultVulnerabilities() - id-bugtrack: %s", tmpString.c_str());

					/* cve id */
					nodeTmp = getNodeChild(childVulnerability, "id-cve");
					tmpString = "";
					if (nodeTmp->getFirstChild() != 0)
						tmpString = convertToString(nodeTmp->getFirstChild()->getNodeValue());
					vuln->setCveId(tmpString.c_str());
					getLogger().warn("XPathQueryManager : getXpathResultVulnerabilities() - id-cve: %s", tmpString.c_str());
					
					/* publisher */
					nodeTmp = getNodeChild(childVulnerability, "publisher");
					tmpString = "";
					if (nodeTmp->getFirstChild() != 0)
						tmpString = convertToString(nodeTmp->getFirstChild()->getNodeValue());
					vuln->setPublisher(tmpString.c_str());
					getLogger().warn("XPathQueryManager : getXpathResultVulnerabilities() - publisher: %s", tmpString.c_str());
					
					/* type */
					nodeTmp = getNodeChild(childVulnerability, "type");
					tmpString = "";
					if (nodeTmp->getFirstChild() != 0)
						tmpString = convertToString(nodeTmp->getFirstChild()->getNodeValue());
					vuln->setType(tmpString.c_str());
					getLogger().warn("XPathQueryManager : getXpathResultVulnerabilities() - type: %s", tmpString.c_str());
					
					/* description */
					nodeTmp = getNodeChild(childVulnerability, "description");
					tmpString = "";
					if (nodeTmp->getFirstChild() != 0)
						tmpString = convertToString(nodeTmp->getFirstChild()->getNodeValue());
					vuln->setDescription(tmpString.c_str());
					getLogger().warn("XPathQueryManager : getXpathResultVulnerabilities() - description: %s", tmpString.c_str());					
					
					/* publication date */
					nodeTmp = getNodeChild(childVulnerability, "date-publication");
					tmpString = "";
					if (nodeTmp->getFirstChild() != 0)
						tmpString = convertToString(nodeTmp->getFirstChild()->getNodeValue());
					vuln->setPublicationDate(tmpString.c_str());
					getLogger().warn("XPathQueryManager : getXpathResultVulnerabilities() - publication date: %s", tmpString.c_str());	
					
					/* on recupere les informations pour les vulnérabilités */				
					TCollection<Platform*> *_platforms = new TCollection<Platform*>();
					
					XalanNode *nodePlat = getNodeChild(childVulnerability, "platform");
					while(nodePlat != 0){
						if (nodePlat->getNodeName() == (XalanDOMString)"platform"){
							Platform *platform = new Platform();
							
							nodeTmp = getNodeChild(nodePlat, "name");
							tmpString = convertToString(nodeTmp->getFirstChild()->getNodeValue());
							platform->setName(tmpString);
							getLogger().warn("XPathQueryManager : getXpathResultVulnerabilities() - Nom platforme: %s", tmpString.c_str());

							TCollection<std::string> *distribs = new TCollection<std::string>();
							XalanNode *nodeDistrib = getNodeChild(nodePlat, "distribution");
							while(nodeDistrib != 0){
								if ((nodeDistrib->getNodeName() == (XalanDOMString)"distribution") && (nodeDistrib->getFirstChild() != 0)){
									tmpString = convertToString(nodeDistrib->getFirstChild()->getNodeValue());
									distribs->add(tmpString);
									getLogger().warn("XPathQueryManager : getXpathResultVulnerabilities() - Nom distribution: %s", tmpString.c_str());
								}
								nodeDistrib = nodeDistrib->getNextSibling();
							}
							platform->setDistributions(distribs);
							
							_platforms->add(platform);
						}
						nodePlat = nodePlat->getNextSibling();
					}

					output->add(vuln);
					
				}
			}
		}
		XPathEvaluator::terminate();
		XMLPlatformUtils::Terminate();
	}
    catch(const XSLException& theException) {
    	getLogger().error("XPathQueryManager : getXpathResultVulnerabilities() - XSL exception");
		return 0;
    }
	catch(...) {
		getLogger().error("XPathQueryManager : getXpathResultVulnerabilities() - Generic exception caught!");
		return 0;
	}
		
	getLogger().debug("XPathQueryManager : getXpathResultVulnerabilities() - end");
	return output;
}


/**
 * recupere les exploits pour une vulnérabilité donnée.
 * 
 */
TCollection<Exploit*> *XPathQueryManager::getXpathResultExploits(const std::string xPathQuery, const std::string contextNode) {
	
	getLogger().debug("XPathQueryManager : getXpathResultExploits() - begin");
	TCollection<Exploit*> *output = new TCollection<Exploit*>();

	XALAN_USING_XALAN(XSLException)

    try {
		XALAN_USING_XERCES(XMLPlatformUtils)
		XALAN_USING_XALAN(XPathEvaluator)

		XMLPlatformUtils::Initialize();
		XPathEvaluator::initialize();

		{
			XALAN_USING_XERCES(LocalFileInputSource)
			XALAN_USING_XALAN(XalanDocument)
			XALAN_USING_XALAN(XalanDocumentPrefixResolver)
			XALAN_USING_XALAN(XalanDOMString)
			XALAN_USING_XALAN(XalanNode)
			XALAN_USING_XALAN(XalanEmptyNamedNodeMap)
			XALAN_USING_XALAN(XalanSourceTreeDOMSupport)
			XALAN_USING_XALAN(XalanSourceTreeParserLiaison)
			XALAN_USING_XALAN(XObjectPtr)
			XALAN_USING_XALAN(XalanNodeListDummy)
			XALAN_USING_XALAN(XalanElement)

			// We'll use these to parse the XML file.
			XalanSourceTreeDOMSupport theDOMSupport;
			XalanSourceTreeParserLiaison theLiaison(theDOMSupport);

			// Hook the two together...
			theDOMSupport.setParserLiaison(&theLiaison);

			const XalanDOMString theFileName(_file_name.c_str());

			// Create an input source that represents a local file...
			const LocalFileInputSource theInputSource(theFileName.c_str());

			// Parse the document...
			XalanDocument* const theDocument = theLiaison.parseXMLStream(theInputSource);
			assert(theDocument != 0);

			XalanDocumentPrefixResolver	thePrefixResolver(theDocument);

			XPathEvaluator theEvaluator;

			// OK, let's find the context node...
			XalanNode* const theContextNode =
					theEvaluator.selectSingleNode(
						theDOMSupport,
						theDocument,
						XalanDOMString(contextNode.c_str()).c_str(),
						thePrefixResolver);

			if (theContextNode == 0) {
				getLogger().warn("XPathQueryManager : getXpathResultExploits() - No nodes matched the location path");
			} else {
				// OK, let's evaluate the expression...
				const XObjectPtr theResult(
					theEvaluator.evaluate(
							theDOMSupport,
							theContextNode,
							XalanDOMString(xPathQuery.c_str()).c_str(),
							thePrefixResolver));

				assert(theResult.null() == false);
				
				const XALAN_CPP_NAMESPACE::NodeRefListBase& nodeset = theResult->nodeset();

				XalanNode *nodeVuln = (XalanNode *)nodeset.item(0);
				
				// on vérifie si on est bien sur le noeud "vulnerablity" du fichier expl.xml
				if (nodeVuln->getNodeName() != (XalanDOMString)"vulnerability"){
					return output;
				}
				
				// on veut ensuite récuperer les id des noeuds fils "exploit"
				XalanNode *nodeExploit = nodeVuln->getFirstChild();
				while(nodeExploit != 0){
					if (nodeExploit->getNodeName() == (XalanDOMString)"exploit"){
						Exploit *exploit = new Exploit();
						
						std::string idExploit = getAttributeByName(nodeExploit,"id");
						
						getLogger().warn("XPathQueryManager : getXpathResultExploits() - id exploit: %s", idExploit.c_str());
						
						// on récupere ensuite les informations contenus dans le fichier [idExploit].xml

						std::string exploitFileName = "bdd/expl/" + idExploit + ".xml";
						// Create an input source that represents the exploit file.
						const LocalFileInputSource theInputSource(((XalanDOMString)exploitFileName.c_str()).c_str());
						getLogger().warn("XPathQueryManager : getXpathResultExploits() - id exploit: %s", idExploit.c_str());
			
						// Parse the document...
						XalanDocument* const theDocument = theLiaison.parseXMLStream(theInputSource);
						assert(theDocument != 0);

						XalanDocumentPrefixResolver	thePrefixResolver(theDocument);
			
						XPathEvaluator theEvaluator;
			
						// OK, let's find the context node...
						XalanNode* const theContextNode =
								theEvaluator.selectSingleNode(
									theDOMSupport,
									theDocument,
									XalanDOMString("/exploit").c_str(),
									thePrefixResolver);
			
						if (theContextNode == 0) {
							getLogger().debug("XPathQueryManager : getXpathResultExploits() - No nodes matched the location path");
						} else {
							
							// on récupere l'auteur
							std::string query = "informations/author";
							
							const XObjectPtr theResult(
								theEvaluator.evaluate(
										theDOMSupport,
										theContextNode,
										XalanDOMString(query.c_str()).c_str(),
										thePrefixResolver));
			
							assert(theResult.null() == false);
							
							getLogger().debug("XPathQueryManager : getXpathResultExploits() - auteur: %s",convertToString(theResult->str()).c_str());
							exploit->setAuthor(convertToString(theResult->str()).c_str());
							
							// on récupere la description
							query = "informations/description";
							const XObjectPtr theResult2 = theEvaluator.evaluate(
										theDOMSupport,
										theContextNode,
										XalanDOMString(query.c_str()).c_str(),
										thePrefixResolver);
										
							assert(theResult2.null() == false);

							getLogger().debug("XPathQueryManager : getXpathResultExploits() - description: %s",convertToString(theResult2->str()).c_str());
							//exploit->setDescription(convertToString(theResult->str()).c_str());
							
							
							// on récupere les attaques
							TCollection<Attack*> *attacks = new TCollection<Attack*>();
							
							
							query = "attacks/attack";
							const XObjectPtr theResult3 = theEvaluator.evaluate(
										theDOMSupport,
										theContextNode,
										XalanDOMString(query.c_str()).c_str(),
										thePrefixResolver);
										
							assert(theResult3.null() == false);
							
							const XALAN_CPP_NAMESPACE::NodeRefListBase& nodesetAttack = theResult3->nodeset();
							
							for(unsigned int k=0; k<nodesetAttack.getLength(); k++){
								Attack *attack = new Attack();;
								XalanNode *nodeAttack = (XalanNode *)nodesetAttack.item(k);
								
								//num
								std::string tmpString = getAttributeByName(nodeAttack, "num");
								attack->setNum(atoi(tmpString.c_str()));
								getLogger().debug("XPathQueryManager : getXpathResultExploits() - num: %d", atoi(tmpString.c_str()));
					
								//type
								XalanNode *tmpNode = getNodeChild(nodeAttack,"type")->getFirstChild();
								attack->setType(convertToString(tmpNode->getNodeValue()).c_str());
								getLogger().debug("XPathQueryManager : getXpathResultExploits() - attackType: %s",convertToString(tmpNode->getNodeValue()).c_str());
								
								//language
								tmpNode = getNodeChild(nodeAttack,"language")->getFirstChild();
								attack->setLanguage(convertToString(tmpNode->getNodeValue()).c_str());
								getLogger().debug("XPathQueryManager : getXpathResultExploits() - attackLanguage: %s",convertToString(tmpNode->getNodeValue()).c_str());
								
								//command
								tmpNode = getNodeChild(nodeAttack,"command")->getFirstChild();
								attack->setCommand(convertToString(tmpNode->getNodeValue()).c_str());
								getLogger().debug("XPathQueryManager : getXpathResultExploits() - attackCommand: %s",convertToString(tmpNode->getNodeValue()).c_str());
								
								//code
								tmpNode = getNodeChild(nodeAttack,"code")->getFirstChild();
								attack->setCode(convertToString(tmpNode->getNodeValue()).c_str());
								//getLogger().debug("XPathQueryManager : getXpathResultExploits() - attackCode: %s",convertToString(tmpNode->getNodeValue()).c_str());
								
								attacks->add(attack);
							}
							
							exploit->setAttacks(attacks);
						}

						output->add(exploit);
					}
					nodeExploit = nodeExploit->getNextSibling();
				}
					
			}
		}
		XPathEvaluator::terminate();
		XMLPlatformUtils::Terminate();
	}
    catch(const XSLException& theException) {
    	getLogger().error("XPathQueryManager : getXpathResultExploits() - XSL exception");
		return 0;
    }
	catch(...) {
		getLogger().error("XPathQueryManager : getXpathResultExploits() - Generic exception caught!");
		return 0;
	}
	
	getLogger().debug("XPathQueryManager : getXpathResultExploits() - end");
	return output;
}




