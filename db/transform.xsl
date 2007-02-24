<?xml version="1.0" encoding="UTF-8"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">
    <xsl:output method="xml" indent="yes" encoding="UTF-8" version="1.0"/>
    
    <xsl:template match="/report">
        <result>
            <xsl:apply-templates select="results/result/host"/>
            <system>
                <xsl:value-of select="results/result/ports/port/information[id/text()=11936]/data"/>
            </system>
            <ports>
                <xsl:apply-templates select="results/result/ports/port[@portid!='']"/>
            </ports>
        </result>
    </xsl:template>
    
    <xsl:template match="host">
        <xsl:element name="host">
            <xsl:attribute name="name">
                <xsl:value-of select="@name"/>
            </xsl:attribute>
            <xsl:attribute name="ip">
                <xsl:value-of select="@ip"/>
            </xsl:attribute>
        </xsl:element>
    </xsl:template>
    
    <xsl:template match="port">
        <xsl:element name="port">
            <xsl:attribute name="protocol">
                <xsl:value-of select="@protocol"/>
            </xsl:attribute>
            <xsl:attribute name="portid">
                <xsl:value-of select="@portid"/>
            </xsl:attribute>
            
            <xsl:apply-templates select="service"/>
            <xsl:apply-templates select="information"/>
            
        </xsl:element>
    </xsl:template>
    
    <xsl:template match="service">
        <xsl:element name="service">
            <xsl:attribute name="name">
                <xsl:value-of select="@name"/>
            </xsl:attribute>
        </xsl:element>
    </xsl:template>
    
    <xsl:template match="information">
        <xsl:variable name="id">
            <xsl:value-of select="id"/>
        </xsl:variable>
        <xsl:variable name="data">
            <xsl:value-of select="data"/>
        </xsl:variable>
        
        <xsl:if test="/report/plugins/plugin[@id=$id]/risk/text() != 'None'">
            <xsl:if test="/report/plugins/plugin[@id=$id]/risk/text() != 'Low'">
                <information>
                    <id>
                        <xsl:value-of select="$id"/>
                    </id>
                    
                    <xsl:apply-templates select="//plugin">
                        <xsl:with-param name="id" select="$id"/>
                    </xsl:apply-templates>
                    
                </information>
            </xsl:if>
        </xsl:if>
    </xsl:template>
    
    <xsl:template match="plugin">
        <xsl:param name="id"/>
        <xsl:variable name="name">
            <xsl:value-of select="name"/>
        </xsl:variable>
        <xsl:variable name="family">
            <xsl:value-of select="family"/>
        </xsl:variable>
        <xsl:variable name="cve_id">
            <xsl:value-of select="cve_id"/>
        </xsl:variable>
        <xsl:variable name="bugtraq_id">
            <xsl:value-of select="bugtraq_id"/>
        </xsl:variable>
        <xsl:variable name="category">
            <xsl:value-of select="category"/>
        </xsl:variable>
        <xsl:variable name="risk">
            <xsl:value-of select="risk"/>
        </xsl:variable>
        <xsl:if test="@id = $id">
            <name>
                <xsl:value-of select="$name"/>
            </name>   
            <family>
                <xsl:value-of select="$family"/>
            </family> 
            <cve_id>
                <xsl:value-of select="$cve_id"/>
            </cve_id>
            <bugtraq_id>
                <xsl:value-of select="$bugtraq_id"/>
            </bugtraq_id> 
            <category>
                <xsl:value-of select="$category"/>
            </category>  
            <risk>
                <xsl:value-of select="$risk"/>
            </risk>               
        </xsl:if>
    </xsl:template>
    
</xsl:stylesheet>


