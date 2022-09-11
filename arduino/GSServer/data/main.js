'use strick';

let host = ''
host = 'http://gs.local'

const LAUNCHER_MODE = false

const POLLING_FREQ = 1
const MAX_PLOT_ELEMENT = 2000

let remote_index = 0;
let local_index = 0;

let remote_packets = {};
let local_packets = {};

Chart.defaults.global.defaultFontColor = "#fff";

const command_format = {
  'B': {
    name: 'Battery',
    entries: {
      'P': { name: 'Vpp', unit: 'V', datatype: 'float', normal: 9.00 },
      'C': { name: 'Vcc', unit: 'V', datatype: 'float', normal: 5.00 },
      'D': { name: 'Vdd', unit: 'V', datatype: 'float', normal: 3.30 },
      'c': { name: 'Vcc', unit: 'A', datatype: 'float' },
      'd': { name: 'Vdd', unit: 'A', datatype: 'float' },
    }
  },
  'P': {
    name: 'GPS',
    entries: {
      'O': { name: 'Longitude', unit: '°', datatype: 'float' },
      'A': { name: 'Latitude',  unit: '°', datatype: 'float' },
      'H': { name: 'Altitude',  unit: 'm', datatype: 'float' },
      'T': { name: 'Time',      unit: 's', datatype: 'time' },
    }
  },
  'S': {
    name: 'LoRa TX',
    entries: {
      'C': { name: 'Code', datatype: 'int' },
      'O': { name: 'OK', datatype: 'uint' },
      'E': { name: 'NG', datatype: 'uint' },
    }
  },
  'R': {
    name: 'LoRa RX',
    entries: {
      'R': { name: 'RSSI', unit: 'dBm', datatype: 'int' },
      'C': { name: 'Count', datatype: 'uint' },
    }
  },

  // Telemetry and Command
  'n': {
    name: 'Navigation',
    entries: {
      'O': { name: 'Longitude', unit: '°', datatype: 'float' },
      'A': { name: 'Latitude',  unit: '°', datatype: 'float' },
      'H': { name: 'GPS Alt',  unit: 'm', datatype: 'float' },
      'P': { name: 'Pressure Alt',  unit: 'm', datatype: 'float' },
    }
  },
  'm': {
    name: 'Mode',
    entries: {
      'N': { name: 'Launch', payload: 'No', error: true },
      'A': { name: 'Launch', payload: 'Allow' },
      'S': { name: 'Mode', payload: 'Standby'  },
      'F': { name: 'Mode', payload: 'Flight' },
      'L': { name: 'Mode', payload: 'Launch' },
    }
  },
  's': {
    name: 'Settings',
    entries: {
      'I': { name: 'Min Launch Alt', unit: 'm', datatype: 'float' },
      'S': { name: 'Std Launch Alt', unit: 'm', datatype: 'float' },
      'A': { name: 'Max Launch Alt', unit: 'm', datatype: 'float' },
      'Q': { name: 'QNH', unit: 'hPa', datatype: 'float' },
    }
  },

  // Command


  'Sample': {
    name: 'Sample',
    entries: {
      'P': { name: 'Vpp', unit: 'V', datatype: 'float', normal: 9.0 },
      'C': { name: 'Vcc', unit: 'V', datatype: 'float', normal: 5.0 },
      'D': { name: 'Vdd', unit: 'V', datatype: 'float', normal: 3.3 },
      'c': { name: 'Vcc', unit: 'A', datatype: 'float', },
      'd': { name: 'Vdd', unit: 'A', datatype: 'float', },
    }
  },
}

const charts = [
  {
    name: 'Launcher Location',
    local: LAUNCHER_MODE,
    id: 'P',
    x: 'O',
    y: ['A'],
    xLabel: 'Longitude [deg]',
    yLabel: 'Latitude [deg]'
  },
  {
    name: 'Launcher Altitude',
    local: LAUNCHER_MODE,
    id: 'P',
    x: 't',
    y: ['H'],
    xLabel: 't [ms]',
    yLabel: 'Altitude [m]'
  },
  {
    name: 'Launcher Battery',
    local: LAUNCHER_MODE,
    id: 'B',
    x: 't',
    y: ['P', 'C', 'D'],
    xLabel: 't [ms]',
    yLabel: 'Voltage [V]',
    // yMin: 0,
    // yMax: 15
  },
  {
    name: 'LoRa RX',
    local: true,
    id: 'R',
    x: 't',
    y: ['R'],
    xLabel: 't [ms]',
    yLabel: 'RSSI [V]',
    yMax: 0,
  },
  {
    name: 'GS Location',
    local: true,
    id: 'P',
    x: 'O',
    y: ['A'],
    xLabel: 'Longitude [deg]',
    yLabel: 'Latitude [deg]'
  },
  {
    name: 'GS Battery',
    local: !LAUNCHER_MODE,
    id: 'B',
    x: 't',
    y: ['P', 'C', 'D'],
    xLabel: 't [ms]',
    yLabel: 'Voltage [V]',
    // yMin: 0,
    // yMax: 10,
  },
]

function createCharts() {
  for (const chart of charts) {
    const canvas = $('<canvas></canvas>');
    $('#charts').append(canvas);

    const data = {
      lebals: [],
      datasets: chart.y.map(entry_type => {
        const command = command_format[chart.id];
        return {
          entry_type: entry_type,
          label: command.entries[entry_type].name,
          data: [],
          showLine: true,
          fill: false,
          pointRadius: 0,
        }
      })
    }
    const config = {
      type: chart.type || 'scatter',
      data: data,
      options: {
        title: {
          display: true,
          text: chart.name,
        },
        element: {
          point: {
            radius: 0,
          }
        },
        legend: {
          display: chart.y.length > 1
        },
        scales: {
          xAxes: [{
            display: true,
            gridLines: {
              color: '#606060'
            },
            ticks:  {
              min: chart.xMin,
              max: chart.xMax
            },
            scaleLabel: {
              display: true,
              labelString: chart.xLabel
            }
          }],
          yAxes: [{
            display: true,
            gridLines: {
              color: '#606060'
            },
            ticks:  {
              min: chart.yMin,
              max: chart.yMax
            },
            scaleLabel: {
              display: true,
              labelString: chart.yLabel
            }}
          ]
        },
        animation: false,
      }
    }

    chart.chart = new Chart(canvas, config);
  }
}

function addHistory(command) {

  for (chart of charts) {
    if (chart.id == command.id && chart.local == command.local) {
      const x = command.entries.find(entry => entry.type == chart.x).payload;
      chart.chart.data.datasets.forEach((dataset) => {
        if (dataset.data.length > MAX_PLOT_ELEMENT) {
          let data = [];
          for (let i = 0; i < Math.floor(dataset.data.length / 2); i++) {
            if (i * 2 + 1 == dataset.data.length) {
              data.push(dataset.data[i * 2]);
            }
            else {
              data.push({
                x: (dataset.data[i * 2].x + dataset.data[i * 2 + 1].x) / 2,
                y: (dataset.data[i * 2].y + dataset.data[i * 2 + 1].y) / 2,
              })
            }
          }
          dataset.data = data;
        }
        const y = command.entries.find(
          entry => entry.type == dataset.entry_type).payload;
        dataset.data.push({x, y});
      })
      chart.chart.update();
    }
  }
}

function main() {
  setInterval(() => {
    fetch(true);
    setTimeout(() => {
      fetch(false);
    }, 1000 / POLLING_FREQ / 2);
  }, 1000 / POLLING_FREQ);

  $('#connection-error').hide();

  let sample_format = command_format['Sample'];
  let sample = { name: sample_format.name, id: 'S', to: 'G', from: 'G',
                 size: 5, entries: [], t: 1234567};
  for (let k in sample_format.entries) {
    let entry = {};
    Object.assign(entry, sample_format.entries[k]);
    entry.payload = Math.random();
    sample.entries.push(entry)
  }
  console.log(sample);

  createCharts();
  render();
}

function fetch(local) {
  // local_packets['Sample'].updated = true;

  if (local) {
    for (let id in local_packets) {
      local_packets[id].updated = false;
    }
  }
  else {
    for (let id in remote_packets) {
      remote_packets[id].updated = false;
    }
  }

  // if (local) console.log('fetch local',  local_index);
  // else console.log('fetch remote',  remote_index);

  $.ajax({
    url: host + (local ? '/local' : '/remote'),
    type: 'GET',
    data: { index: local ? local_index : remote_index },
    dataType: 'text',
    async: true,
    cache: false,
    timeout: 1000 / POLLING_FREQ}).then((str) => {
      $('#connection-error').hide();

      const lines = str.split('\n').filter(line => line != "");

      console.log('returned', parseInt(lines[0]));

      if (local) local_index = parseInt(lines[0]);
      else remote_index = parseInt(lines[0]);

      lines.shift();

      const commands = lines.map(parseCommandHex);

      commands.forEach((command, i) => {
        console.log('command ' + ((local ? local_index : remote_index ) + i),
                    command);
        command.updated = true;
        command.date = new Date();
        command.local = local;

        addHistory(command);

        if (local) local_packets[command.id] = command;
        else remote_packets[command.id] = command;
      });

      render(local);
    }).catch((e) => {
      $('#connection-error').show();
      console.error(e);
      render(local);
    });
}

function render(local) {
  // $('#rocket-packets').empty();
  // for (let id in rocket_packets) {
  //   $('#rocket-packets').append(commandItem(rocket_packets[id]));
  // }
  if (local) {
    $('#local-packets').empty();
    for (let id in local_packets) {
      $('#local-packets').append(commandItem(local_packets[id]));
    }
  }
  else {
    $('#remote-packets').empty();
    for (let id in remote_packets) {
      $('#remote-packets').append(commandItem(remote_packets[id]));
    }
  }
}

function commandItem(command) {
  return `<table class="pure-table pure-table-horizontal command
                         ${command.updated ? 'updated' : ''}">
            <thead>
               <tr>
                 <th>${command.name}</th>
                 <th>${showMillis(command.t)}</th>
               </tr>
            </thead>
            ${command.entries.map(entryItem).join('\n')}
          </table>`
}
function entryItem(entry) {
  if (entry.type == 't') return '';

  let payload = entry.payload;
  if (entry.datatype == 'float')
    payload = String(entry.payload).slice(0, 11);
  else if (entry.datatype == 'time')
    payload = payload.toLocaleTimeString('ja-JP');

  let normal = entry.normal;
  if (normal && entry.datatype == 'float') normal = normal.toFixed(4);

  return `<tr class="${entry.error ? 'error' : ''}">
            <td>${entry.name} ${entry.unit ? '[' + entry.unit + ']' : ''}</td>
            <td>${payload == null ? '' : payload}</td>
          </tr>`;
}

function parseCommandHex(line) {
  const hexes = line.replace(/\r?\n/g, '').match(/.{2}/g);
  const bytes = hexes.map(hex => parseInt(hex, 16));

  const id = String.fromCharCode(bytes[1]);
  const to = String.fromCharCode(bytes[2]);
  const from = String.fromCharCode(bytes[3]);
  const size = bytes[4];

  const format = command_format[id];
  let command = {id: id, to: to, from: from, size: size,
                 name: format && format.name,
                 hex: line, t: null,
                 entries: []}

  let i = 5;
  while (true) {
    if (i >= bytes.length) break;

    const type = String.fromCharCode(bytes[i] & 0b01111111);

    let entry = {type: type};

    if (format && format.entries[type]) {
      Object.assign(entry, format.entries[type]);
    }
    else {
      entry.name = type;
    }


    if (bytes[i] & 0b10000000) {
      i += 1;
    }
    else {
      let buf = new ArrayBuffer(4);
      let view = new DataView(buf);
      for (let n = 0; n < 4; n++) {
        view.setUint8(3 - n, bytes[i + n + 1]);
      }

      if (entry.payload != undefined) {
      }
      else if (type == 't') {
        entry.payload = view.getUint32(0);
        command.t = entry.payload;
      }
      else if (format && format.entries[type]) {
        switch (format.entries[type].datatype) {
        case 'float':
          entry.payload = view.getFloat32(0);
          break;
        case 'int':
          entry.payload = view.getInt32(0);
          break;
        case 'time':
          entry.payload = new Date(view.getUint32(0) * 1000);
          break;
        case undefined:
          entry.payload = null;
          break;
        default:
          entry.payload = line.slice(i * 2 + 2, i * 2 + 12);
          break;
        }
      }
      else {
        entry.payload = line.slice(i * 2 + 2, i * 2 + 12);
      }

      i += 5;
    }

    command.entries.push(entry);
  }

  return command;
}

function showMillis(t) {
  const ms = t % 1000;
  const s = Math.floor(t / 1000) % 60;
  const m = Math.floor(t / 1000 / 60) % 60;
  const h = Math.floor(t / 1000 / 60 / 60) % 24;

  return String(h) + ':'
    + String(m).padStart(2, '0') + ':'
    + String(s).padStart(2, '0') + '.'
    + String(ms).padStart(4, '0');
}

window.addEventListener('load', main);

