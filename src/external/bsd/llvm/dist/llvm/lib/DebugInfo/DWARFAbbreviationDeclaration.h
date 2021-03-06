//===-- DWARFAbbreviationDeclaration.h --------------------------*- C++ -*-===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

#ifndef LLVM_DEBUGINFO_DWARFABBREVIATIONDECLARATION_H
#define LLVM_DEBUGINFO_DWARFABBREVIATIONDECLARATION_H

#include "llvm/ADT/SmallVector.h"
#include "llvm/Support/DataExtractor.h"

namespace llvm {

class raw_ostream;

class DWARFAbbreviationDeclaration {
  uint32_t Code;
  uint32_t Tag;
  bool HasChildren;

  struct AttributeSpec {
    AttributeSpec(uint16_t Attr, uint16_t Form) : Attr(Attr), Form(Form) {}
    uint16_t Attr;
    uint16_t Form;
  };
  SmallVector<AttributeSpec, 8> Attributes;
public:
  DWARFAbbreviationDeclaration();

  uint32_t getCode() const { return Code; }
  uint32_t getTag() const { return Tag; }
  bool hasChildren() const { return HasChildren; }
  uint32_t getNumAttributes() const { return Attributes.size(); }
  uint16_t getAttrByIndex(uint32_t idx) const {
    return idx < Attributes.size() ? Attributes[idx].Attr : 0;
  }
  uint16_t getFormByIndex(uint32_t idx) const {
    return idx < Attributes.size() ? Attributes[idx].Form : 0;
  }

  uint32_t findAttributeIndex(uint16_t attr) const;
  bool extract(DataExtractor Data, uint32_t* OffsetPtr);
  void dump(raw_ostream &OS) const;

private:
  void clear();
};

}

#endif
