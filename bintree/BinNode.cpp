#include"BinNode.h"

template<typename T>
int BinNode<T>::size()
{
	//TODO
	return 0;
}

template<typename T>
inline BNPosi(T) BinNode<T>::insertAsLc(T const & e)
{
	return lc=new BinNode(e,this);
}

template<typename T>
inline BNPosi(T) BinNode<T>::insertAsRc(T const &)
{
	return rc=new BinNode(e,this);
}

template<typename T> 
BNPosi(T) BinNode<T>::succ()//仅中序遍历下的直接后续如此
{
	BNPosi(T) s = this;
	if (rc) {
		s = rc;
		while (HasLChild(*s)) s = s->lc;
	}
	else {
		while (IsRChild(*s)) s = s->parent;
		s = s->parent;
	}
	return s;
}

template<typename T>
template<typename VST>
void BinNode<T>::travIn(VST &visit)
{
	switch (rand()%5)
	{
		case 1:travIn_I1(this, visit); break;
		case 2:travIn_I2(this, visit); break;
		case 3:travIn_I3(this, visit); break;
		case 4:travIn_I4(this, visit); break;
		default:travIn_R(this, visit); break;
	}
}

template<typename T>
template<typename VST>
void BinNode<T>::travLevel(VST &visit)
{
	switch (rand() % 5)
	{
	case 1:travLe_L1(this, visit); break;
	case 2:travLe_L2(this, visit); break;
	case 3:travLe_L3(this, visit); break;
	case 4:travLe_L4(this, visit); break;
	default:travLe_R(this, visit); break;
	}
}

template<typename T>
template<typename VST>
void BinNode<T>::travPre(VST &visit)
{
	switch (rand() % 5)
	{
	case 1:travPre_1(this, visit); break;
	case 2:travPre_2(this, visit); break;
	case 3:travPre_3(this, visit); break;
	case 4:travPre_4(this, visit); break;
	default:travPre_R(this, visit); break;
	}
}

template<typename T>
template<typename VST>
void BinNode<T>::travPost(VST &visit)
{
	switch (rand() % 5)
	{
	case 1:travPost_1(this, visit); break;
	case 2:travPost_2(this, visit); break;
	case 3:travPost_3(this, visit); break;
	case 4:travPost_4(this, visit); break;
	default:travPost_R(this, visit); break;
	}
}