//
//  DroiObjectTest.hpp
//  TestGame
//
//  Created by jiang on 16/11/17.
//
//

#include "DroiObject.h"
#include "DroiQuery.h"
#include "DroiCondition.h"

class DroiObjectTest : public DroiObject
{
public:
    DroiObjectTest() : DroiObject("ScoreTable"){
        
    }
    
    // 使用者名称Getter
    std::string getName() {
        std::string name;
        
        getValue( "name", name );
        return name;
    }
    
    // 使用者名称Setter
    void setName( const std::string& name ) {
        setValue( "name", name );
    }
    
    // 密码Getter
    std::string getPassword() {
        std::string password;
        
        getValue( "password", password );
        return password;
    }
    
    // 密码Setter
    void setPassword( const std::string& password ) {
        setValue( "password", password );
    }
    
    // 性別Getter
    std::string getGender() {
        std::string gender;
        
        getValue( "gender", gender );
        return gender;
    }
    
    // 性別Setter
    void setGender( const std::string& gender ) {
        setValue( "gender", gender );
    }
    
    void query(){
        DroiQuery* query = DroiQuery::create();
        
        // 设定查询条件。
        query->queryData( "Book" )	// 由Book表格取得
        .where(DroiCondition::eq( "price", Value(70) )) // price等于70
        .orderBy( "ISBN", false );	// 依照ISBN做descending排序
        
        DroiError err;
        RefVector* result = query->runQuery(&err);
        if ( err.isOk() ) {
            // 成功
        }
    }
};
