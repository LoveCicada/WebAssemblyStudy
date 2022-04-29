var Module = {



  onRuntimeInitialized: function() {

   //创建一个cChartViewProperty2类对象
  let cChartViewProperty2 = new Module['CChartViewProperty']("speed",120,130);
  //打印该对象
  console.log(cChartViewProperty2);
  //打印该对象的私有成员变量x的值
  console.log(cChartViewProperty2['strTitle']);
  console.log(cChartViewProperty2['dWidth']);
  console.log(cChartViewProperty2['color']);
  //通过set函数赋值

  cChartViewProperty2['strTitle']='speed';
  cChartViewProperty2['dWidth']=102;
  cChartViewProperty2['color']=222;
  //再次打印该对象的私有成员变量x的值

  console.log(cChartViewProperty2['strTitle']);
  console.log(cChartViewProperty2['dWidth']);
  console.log(cChartViewProperty2['color']);

  // ChartViewPropertyVec propertyVec;
  let propertyVec = new Module['ChartViewPropertyVec'];
  propertyVec.push_back(cChartViewProperty2);
  
  let parameterData = new Module['CParameterData'](10,23.32);
  console.log(parameterData);
  console.log(parameterData['dValue']);

  let parameterDataVec = new Module['ParameterDataVector'];
  parameterDataVec.push_back(parameterData);

  let flightItemData = new Module['CFlightItemData'];
  flightItemData['strLabel']="height";
  flightItemData['strCategory']="strCategory";
  flightItemData['ParameterDataVector']=parameterDataVec;

  let flightItemDataVector = new Module['FlightItemDataVector'];
  flightItemDataVector.push_back(flightItemData);


  let ret = Module.setChartData(propertyVec, flightItemDataVector);
  console.log(ret);


  //析构该对象实例，释放wasm共享线性内存空间
  cChartViewProperty2.delete();


  }




};
