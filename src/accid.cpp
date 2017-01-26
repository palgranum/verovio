/////////////////////////////////////////////////////////////////////////////
// Name:        accid.cpp
// Author:      Laurent Pugin
// Created:     2014
// Copyright (c) Authors and others. All rights reserved.
/////////////////////////////////////////////////////////////////////////////

#include "accid.h"

//----------------------------------------------------------------------------

#include <assert.h>

//----------------------------------------------------------------------------

#include "functorparams.h"
#include "note.h"
#include "smufl.h"

namespace vrv {

//----------------------------------------------------------------------------
// Accid
//----------------------------------------------------------------------------

Accid::Accid()
    : LayerElement("accid-"), PositionInterface(), AttAccidental(), AttAccidLog(), AttColor(), AttEnclosingchars()
{

    RegisterInterface(PositionInterface::GetAttClasses(), PositionInterface::IsInterface());
    RegisterAttClass(ATT_ACCIDENTAL);
    RegisterAttClass(ATT_ACCIDENTALPERFORMED);
    RegisterAttClass(ATT_ACCIDLOG);
    RegisterAttClass(ATT_COLOR);
    RegisterAttClass(ATT_ENCLOSINGCHARS);

    Reset();
}

Accid::~Accid()
{
}

void Accid::Reset()
{
    LayerElement::Reset();
    PositionInterface::Reset();
    ResetAccidental();
    ResetAccidentalPerformed();
    ResetAccidLog();
    ResetColor();
    ResetEnclosingchars();
    
    m_drawingCueSize = false;
}

std::wstring Accid::GetSymbolStr() const
{
    if (!this->HasAccid()) return L"";

    int symc = SMUFL_E261_accidentalNatural;
    switch (this->GetAccid()) {
        case ACCIDENTAL_EXPLICIT_s: symc = SMUFL_E262_accidentalSharp; break;
        case ACCIDENTAL_EXPLICIT_f: symc = SMUFL_E260_accidentalFlat; break;
        case ACCIDENTAL_EXPLICIT_ss: symc = SMUFL_E269_accidentalSharpSharp; break;
        case ACCIDENTAL_EXPLICIT_x: symc = SMUFL_E263_accidentalDoubleSharp; break;
        case ACCIDENTAL_EXPLICIT_ff: symc = SMUFL_E264_accidentalDoubleFlat; break;
        case ACCIDENTAL_EXPLICIT_sx:
            symc = SMUFL_E265_accidentalTripleSharp;
            break; // Missing in SMuFL
        case ACCIDENTAL_EXPLICIT_xs: symc = SMUFL_E265_accidentalTripleSharp; break;
        case ACCIDENTAL_EXPLICIT_ts:
            symc = SMUFL_E265_accidentalTripleSharp;
            break; // Missing in SMuFL
        case ACCIDENTAL_EXPLICIT_tf: symc = SMUFL_E266_accidentalTripleFlat; break;
        case ACCIDENTAL_EXPLICIT_n: symc = SMUFL_E261_accidentalNatural; break;
        case ACCIDENTAL_EXPLICIT_nf: symc = SMUFL_E267_accidentalNaturalFlat; break;
        case ACCIDENTAL_EXPLICIT_ns: symc = SMUFL_E268_accidentalNaturalSharp; break;
        case ACCIDENTAL_EXPLICIT_su: symc = SMUFL_E274_accidentalThreeQuarterTonesSharpArrowUp; break;
        case ACCIDENTAL_EXPLICIT_sd: symc = SMUFL_E275_accidentalQuarterToneSharpArrowDown; break;
        case ACCIDENTAL_EXPLICIT_fu: symc = SMUFL_E270_accidentalQuarterToneFlatArrowUp; break;
        case ACCIDENTAL_EXPLICIT_fd: symc = SMUFL_E271_accidentalThreeQuarterTonesFlatArrowDown; break;
        case ACCIDENTAL_EXPLICIT_nu: symc = SMUFL_E272_accidentalQuarterToneSharpNaturalArrowUp; break;
        case ACCIDENTAL_EXPLICIT_nd: symc = SMUFL_E273_accidentalQuarterToneFlatNaturalArrowDown; break;
        case ACCIDENTAL_EXPLICIT_1qf: symc = SMUFL_E280_accidentalQuarterToneFlatStein; break;
        case ACCIDENTAL_EXPLICIT_3qf: symc = SMUFL_E281_accidentalThreeQuarterTonesFlatZimmermann; break;
        case ACCIDENTAL_EXPLICIT_1qs: symc = SMUFL_E282_accidentalQuarterToneSharpStein; break;
        case ACCIDENTAL_EXPLICIT_3qs: symc = SMUFL_E283_accidentalThreeQuarterTonesSharpStein; break;
        default: break;
    }
    std::wstring symbolStr;

    if (this->HasEnclose()) {
        if (this->GetEnclose() == ENCLOSURE_brack) {
            symbolStr.push_back(SMUFL_E26C_accidentalBracketLeft);
            symbolStr.push_back(symc);
            symbolStr.push_back(SMUFL_E26D_accidentalBracketRight);
        }
        else {
            symbolStr.push_back(SMUFL_E26A_accidentalParensLeft);
            symbolStr.push_back(symc);
            symbolStr.push_back(SMUFL_E26B_accidentalParensRight);
        }
    }
    else {
        symbolStr.push_back(symc);
    }
    return symbolStr;
}

//----------------------------------------------------------------------------
// Functor methods
//----------------------------------------------------------------------------

} // namespace vrv