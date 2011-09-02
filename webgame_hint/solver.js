// vim: set et sts=2 sw=2 ts=2 fdm=marker ft=javascript :
/*
var element = document.getElementById('card0');
if (element == null) {
  alert('Card element is not found. Check element id.');
} else {
  var myevent = document.createEvent('MouseEvents');
  myevent.initEvent('click', false, true);
  element.dispatchEvent(myevent);
  alert('Card color is "' + element.style.backgroundColor + '".');
}
*/

var num = 0;
var color = [];
while ((element = document.getElementById('card' + num)) != null) {
  var myevent = document.createEvent('MouseEvents');
  myevent.initEvent('click', false, true);
  element.dispatchEvent(myevent);
  color[num] = element.style.backgroundColor;
  num++;
}

function cardOpen(i) {
  var element = document.getElementById('card' + i);
  var myevent = document.createEvent('MouseEvents');
  myevent.initEvent('click', false, true);
  element.dispatchEvent(myevent);
  color[num] = element.style.backgroundColor;
}

var end = num;
for (var i = 0; i < end; i++) {
  for (var j = 0; j < end; j++) {
    if (i == j) {
      continue;
    } else {
      if (color[i] == color[j]) {
        cardOpen(i);
        cardOpen(j);
      }
    }
  }
}



