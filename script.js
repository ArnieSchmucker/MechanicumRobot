var gateway = `ws://${window.location.hostname}/ws`;
var websocket;
window.addEventListener('load', onLoad);

function onLoad(event) {
  initWebSocket();
  getCurrentValue();
  getCurrentValue_01();
}

function initWebSocket() {
  console.log('Trying to open a WebSocket connection...');
  websocket = new WebSocket(gateway);
  websocket.onopen    = onOpen;
  websocket.onclose   = onClose;
  websocket.onmessage = onMessage;
}

function onOpen(event) {
  console.log('Connection opened');
}
  
function onClose(event) {
  console.log('Connection closed');
  setTimeout(initWebSocket, 2000);
} 

function onMessage(event) {
  console.log(event.data);
}

// Send Requests to Control GPIOs
function toggle (element) {
  console.log(element.id);
  websocket.send(element.id);
}

function getCurrentValue(){
  var xhr = new XMLHttpRequest();
  xhr.onreadystatechange = function() {
    if (this.readyState == 4 && this.status == 200) {
      document.getElementById("pwmSlider").value = this.responseText;
      document.getElementById("textSliderValue").innerHTML = this.responseText;
    }
  };
  xhr.open("GET", "/currentValue", true);
  xhr.send();
}

function getCurrentValue_01(){
  var xhr = new XMLHttpRequest();
  xhr.onreadystatechange = function() {
    if (this.readyState == 4 && this.status == 200) {
      document.getElementById("pincerSlider").value = this.responseText;
      document.getElementById("textPincerSliderValue").innerHTML = this.responseText;
    }
  };
  xhr.open("GET", "/currentValue_01", true);
  xhr.send();
}

function updateSliderPWM(element) {
  var sliderValue = document.getElementById("pwmSlider").value;
  document.getElementById("textSliderValue").innerHTML = sliderValue;
  console.log(sliderValue);
  websocket.send(sliderValue);
}

function updateSliderPincer(element) {
  var pincerValue = document.getElementById("pincerSlider").value;
  document.getElementById("textPincerSliderValue").innerHTML = pincerValue - 200;
  console.log(pincerValue);
  websocket.send(pincerValue);
}

