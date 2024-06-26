#pragma once
#include <unordered_set>
std::vector<FormRecord*> formData;
std::vector<FormRecord*> formRef;

bool espFound = false;
uint32_t lastFormId = 0;  // last mod
uint32_t firstFormId = 0;  // last mod
uint32_t dynamicModId = 0;


void AddFormData(FormRecord* item) {
    if (!item) {
        return;
    }
    formData.push_back(item);
}

void AddFormRef(FormRecord* item) {
    if (!item) {
        return;
    }
    formRef.push_back(item);
}

void EachFormData(std::function<bool(FormRecord*)> const& iteration) {
    for (auto item : formData) {
        if (!iteration(item)) {
            return;
        }
    }
    return;
}

void EachFormRef(std::function<bool(FormRecord*)> const& iteration) {
    for (auto item : formRef) {
        if (!iteration(item)) {
            return;
        }
    }
    return;
}


void incrementLastFormID() {
    ++lastFormId;
}


void UpdateId() {
    EachFormData([&](FormRecord* item) {
        if (item->formId > lastFormId) {
            lastFormId = item->formId;
        }
        return true;
    });
    incrementLastFormID();
}

void ResetId() {
    lastFormId = firstFormId;
}

void ReadFirstFormIdFromESP() {
    const auto dataHandler = RE::TESDataHandler::GetSingleton();

    auto id = dataHandler->LookupFormID(0x800, "Dynamic Persistent Forms.esp");

    if (id != 0) {
        espFound = true;
    }

    firstFormId = id + 1;
    lastFormId = firstFormId;
    dynamicModId = (firstFormId >> 24) & 0xff;
}