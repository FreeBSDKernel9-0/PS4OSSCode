# Copyright (C) 2006, 2007, 2008, 2012 Apple Inc. All rights reserved.
# Copyright (C) 2006 Samuel Weinig <sam.weinig@gmail.com> 
# Copyright (C) 2009 Cameron McCormack <cam@mcc.id.au>
#
# Redistribution and use in source and binary forms, with or without
# modification, are permitted provided that the following conditions
# are met:
#
# 1.  Redistributions of source code must retain the above copyright
#     notice, this list of conditions and the following disclaimer. 
# 2.  Redistributions in binary form must reproduce the above copyright
#     notice, this list of conditions and the following disclaimer in the
#     documentation and/or other materials provided with the distribution. 
# 3.  Neither the name of Apple Computer, Inc. ("Apple") nor the names of
#     its contributors may be used to endorse or promote products derived
#     from this software without specific prior written permission. 
#
# THIS SOFTWARE IS PROVIDED BY APPLE AND ITS CONTRIBUTORS "AS IS" AND ANY
# EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
# WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
# DISCLAIMED. IN NO EVENT SHALL APPLE OR ITS CONTRIBUTORS BE LIABLE FOR ANY
# DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
# (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
# LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
# ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
# (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
# THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

VPATH = \
    $(WebCore) \
    $(WebCore)/Modules/htmltile \
#

BINDING_IDLS = \
    $(WebCore)/Modules/htmltile/HTMLTile.idl \
    $(WebCore)/Modules/htmltile/LocationChangeEvent.idl \
#

.PHONY : all

DOM_CLASSES=$(basename $(notdir $(BINDING_IDLS)))

JS_DOM_HEADERS=$(filter-out JSMediaQueryListListener.h JSEventListener.h JSEventTarget.h, $(DOM_CLASSES:%=JS%.h))

WEB_DOM_HEADERS :=
ifeq ($(findstring BUILDING_WX,$(FEATURE_DEFINES)), BUILDING_WX)
WEB_DOM_HEADERS := $(filter-out WebDOMXSLTProcessor.h WebDOMEventTarget.h, $(DOM_CLASSES:%=WebDOM%.h))
endif # BUILDING_WX

all : \
    $(JS_DOM_HEADERS) \
    $(WEB_DOM_HEADERS) \
    \
#

# --------

# Common generator things

GENERATE_SCRIPTS = \
    bindings/scripts/CodeGenerator.pm \
    bindings/scripts/IDLParser.pm \
    bindings/scripts/IDLStructure.pm \
    bindings/scripts/generate-bindings.pl \
    bindings/scripts/preprocessor.pm

PREPROCESS_IDLS_SCRIPTS = \
    bindings/scripts/IDLParser.pm \
    bindings/scripts/preprocess-idls.pl

generator_script = perl $(addprefix -I $(WebCore)/, $(sort $(dir $(1)))) $(WebCore)/bindings/scripts/generate-bindings.pl

preprocess_idls_script = perl $(addprefix -I $(WebCore)/, $(sort $(dir $(1)))) $(WebCore)/bindings/scripts/preprocess-idls.pl

# JS bindings generator

IDL_INCLUDES = \
    $(WebCore)/dom \
    $(WebCore)/fileapi \
    $(WebCore)/html \
    $(WebCore)/css \
    $(WebCore)/page \
    $(WebCore)/notifications \
    $(WebCore)/xml \
    $(WebCore)/svg

IDL_COMMON_ARGS = $(IDL_INCLUDES:%=--include %) --write-dependencies --outputDir .

JS_BINDINGS_SCRIPTS = $(GENERATE_SCRIPTS) bindings/scripts/CodeGeneratorJS.pm

SUPPLEMENTAL_DEPENDENCY_FILE = ./supplemental_dependency.tmp
IDL_FILES_TMP = ./idl_files.tmp
ADDITIONAL_IDLS = $(WebCore)/inspector/JavaScriptCallFrame.idl
IDL_ATTRIBUTES_FILE = $(WebCore)/bindings/scripts/IDLAttributes.txt

# The following two lines get a space character stored in a variable.
# See <http://blog.jgc.org/2007/06/escaping-comma-and-space-in-gnu-make.html>.
space :=
space +=

$(SUPPLEMENTAL_DEPENDENCY_FILE) : $(PREPROCESS_IDLS_SCRIPTS) $(BINDING_IDLS) $(ADDITIONAL_IDLS) $(IDL_ATTRIBUTES_FILE)
	printf "$(subst $(space),,$(patsubst %,%\n,$(BINDING_IDLS) $(ADDITIONAL_IDLS)))" > $(IDL_FILES_TMP)
	$(call preprocess_idls_script, $(PREPROCESS_IDLS_SCRIPTS)) --defines "$(FEATURE_DEFINES) $(ADDITIONAL_IDL_DEFINES) LANGUAGE_JAVASCRIPT" --idlFilesList $(IDL_FILES_TMP) --supplementalDependencyFile $@ --idlAttributesFile $(IDL_ATTRIBUTES_FILE)
	rm -f $(IDL_FILES_TMP)

JS%.h : %.idl $(JS_BINDINGS_SCRIPTS) $(SUPPLEMENTAL_DEPENDENCY_FILE)
	$(call generator_script, $(JS_BINDINGS_SCRIPTS)) $(IDL_COMMON_ARGS) --defines "$(FEATURE_DEFINES) $(ADDITIONAL_IDL_DEFINES) LANGUAGE_JAVASCRIPT" --generator JS --supplementalDependencyFile $(SUPPLEMENTAL_DEPENDENCY_FILE) $<

