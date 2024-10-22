#include "GameObject.h"
#include "Direct3D.h"

GameObject::GameObject()
	:pParent_(nullptr)
{
}

GameObject::GameObject(GameObject* parent, const std::string& name)
	:pParent_(parent), objectName_(name), isDead_(false)
{
	if (parent != nullptr)
		this->transform_.pParent_ = &(parent->transform_);
}

GameObject::~GameObject()
{
}

void GameObject::DrawSub()
{
	Draw();

	//for(auto itr:childList_)
	for (auto itr = childList_.begin(); itr != childList_.end(); itr++)
	{
		(*itr)->DrawSub();
	}
}

void GameObject::UpdateSub()
{
	Update();

	for (auto itr = childList_.begin(); itr != childList_.end(); itr++)
	{
		(*itr)->UpdateSub();
	}

	for (auto itr=childList_.begin(); itr!=childList_.end(); )
	{
		if ((*itr)->isDead_)
		{
			(*itr)->ReleaseSub();
			//(*itr)->Release();
			SAFE_DELETE(*itr);
			itr = childList_.erase(itr);
		}
		else
		{
			itr++;
		}

	}

}

void GameObject::ReleaseSub()
{
	Release();

	for (auto itr = childList_.begin(); itr != childList_.end(); itr++)
	{
		(*itr)->ReleaseSub();
	}
}

void GameObject::KillMe()
{
	isDead_ = true;
}

GameObject* GameObject::FindObject(string objName)
{
	//考えてみて！
	//自分から見て、ルートジョブを探して、
	// そのルートジョブから全部の子をたどって_objNameを探す！
	GameObject* rootJob = GetRootJob();
	GameObject* result = rootJob->FindChildObject(objName);
	return(result);

}

GameObject* GameObject::GetRootJob()
{
	if (pParent_ == nullptr)
		return this;

	return pParent_->GetRootJob();
}

GameObject* GameObject::FindChildObject(string objName)
{
	if (this->objectName_ == objName)
	{
		return this;
	}
	else
	{
		for (auto itr : childList_)
		{
			GameObject* obj = itr->FindChildObject(objName);
			if(obj != nullptr)
				return obj;
		}
	}
	return nullptr;
}
