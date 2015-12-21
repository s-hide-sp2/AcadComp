#pragma once

//	図面比較API用
namespace acd{
	typedef CMap<int, int, AcDbObjectId, AcDbObjectId> objectIdContainer;

};

namespace zfc{

	// エンティティクローズ関数オブジェクト
	struct closeEntity {
		void operator ()(AcDbEntity* pEnt) {
			auto es = pEnt->close();
			assert( Acad::eOk == es );
		}
	};

	//大文字と小文字を区別せずに2つの文字列を比較する関数オブジェクト
	struct lessNocase {
		bool operator()(const CString& x, const CString& y) const {
			return ( x.CompareNoCase(y) < 0 );
		}
	};

	//	エンティティポインタタイプ定義
	typedef std::unique_ptr<AcDbEntity, closeEntity> entityPtr;

	//	エンティティコンテナタイプ定義(key=図形ハンドル, value=エンティティ)
	typedef std::map<CString, entityPtr> entityContainer;

	//	パスコンテナタイプ定義(key=ファイルタイトル, value=ファイルパス)
	typedef std::map<CString, CString, lessNocase> pathContainer;
	
	// for_each の引数を簡略化するテンプレート関数
	template <typename T_container, typename T_function>
	T_function for_each(T_container& rcontainer, T_function function) {
		return std::for_each(rcontainer.begin(), rcontainer.end(), function);
	}
};