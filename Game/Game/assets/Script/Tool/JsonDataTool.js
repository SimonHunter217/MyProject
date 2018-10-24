/*global module, require, cc, client */
/**
 * @desc 获取配置刷出来的JSON数据
 * @author Administrator
 */
var outModule = {};
//以名字来做key
//一个key对应一个obj，obj里面有两个属性，一个是object（用对象的方式组织数据），一个是array（用数组的方式实现）
var localJsonDataSave = {};

outModule.init = (finishCb) => {
    cc.loader.loadResDir('Excel_Data', function (err, objects, urls) {
        urls.forEach(function (oneUrl, index) {
            oneUrl = oneUrl.replace("Excel_Data/", "");
            localJsonDataSave[oneUrl] = objects[index];
        });
        if (finishCb) {
            finishCb();
        }
    });
};

//根据一个key值来获取数据，返回一个数组
outModule.getDataByKey = (tableName, key, value) => {
    let table = outModule.getTableByName(tableName);
    if (table && table.array) {
        let returnArr = [];
        table.array.forEach((oneData) => {
            if (oneData[key] === value) {
                returnArr.push(oneData);
            }
        });
        return returnArr;
    }
    return [];
};

outModule.getTableByName = (tableName) => {
    return localJsonDataSave[tableName];
};

outModule.getDataById = (tableName, id) => {
    if (localJsonDataSave[tableName]) {
        return localJsonDataSave[tableName].object[id];
    }
    return undefined;
};

module.exports = outModule;