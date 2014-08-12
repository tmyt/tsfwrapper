#include "pch.h"

#include "Composition.h"

using namespace TextServiceFramework;

Composition^ Composition::instance;

Composition::Composition()
{
	CoCreateInstance(CLSID_TF_ThreadMgr, nullptr, CLSCTX_INPROC_SERVER, IID_PPV_ARGS(&mgr));
}

bool Composition::getIsInComposition()
{
	CComQIPtr<IEnumTfDocumentMgrs> enumDocMgr;
	mgr->EnumDocumentMgrs(&enumDocMgr);
	auto docMgrs = convertToVector<ITfDocumentMgr>(enumDocMgr.p);
	for (const auto& doc : docMgrs)
	{
		CComQIPtr<IEnumTfContexts> enumContexts;
		doc->EnumContexts(&enumContexts);
		auto contexts = convertToVector<ITfContext>(enumContexts.p);
		for (const auto& context : contexts)
		{
			CComQIPtr<ITfContextOwnerCompositionServices> compositionService(context);
			CComQIPtr<IEnumITfCompositionView> enumCompositions;
			compositionService->EnumCompositions(&enumCompositions);
			auto compositions = convertToVector<ITfCompositionView>(enumCompositions.p);
			if (compositions.size()) return true;
		}
	}
	return false;
}
