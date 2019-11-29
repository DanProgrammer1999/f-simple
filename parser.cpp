#include "parser.h"

Integer *toInteger(Element *element) {
    switch (element->getExecType()) {
        case typeInteger:
            return Integer::fromElement(element);
        case typeReal:
            return new Integer(static_cast<int>(Real::fromElement(element)->value));
        case typeBoolean:
            return Boolean::fromElement(element)->value ? new Integer(1) : new Integer(0);
        case typeNil:
            return new Integer(0);
        default:
            return nullptr;
    }
}

Real *toReal(Element *element) {
    switch (element->getExecType()) {
        case typeInteger:
            return new Real((double)Integer::fromElement(element)->value);
        case typeReal:
            return Real::fromElement(element);
        case typeBoolean:
            return Boolean::fromElement(element)->value ? new Real(1.0) : new Real(0.0);
        case typeNil:
            return new Real(0.0);
        default:
            return nullptr;
    }
}

Boolean *toBool(Element *element) {
    switch (element->getExecType()) {
        case typeInteger:
            return Integer::fromElement(element)->value > 0 ? new Boolean(true) : new Boolean(false);
        case typeReal:
            return Real::fromElement(element)->value > 0 ? new Boolean(true) : new Boolean(false);
        case typeBoolean:
            return Boolean::fromElement(element);
        case typeNil:
            return new Boolean(false);
        case typeList:
            return List::fromElement(element)->elements.size() > 0 ? new Boolean(1) : new Boolean(0);
        default:
            return nullptr;
    }
}
