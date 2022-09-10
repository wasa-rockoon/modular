'use strick';

host = 'http://192.168.1.1'

const POLLING_FREQ = 1

let tlm_index = -1;
let gs_index = -1;

let tlm_packets = {};
let gs_packets = {};

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
      'C': { name: 'Code', unit: '', datatype: 'int' },
    }
  },
  'R': {
    name: 'LoRa RX',
    entries: {
      'R': { name: 'RSSI', unit: 'dBm', datatype: 'int' },
    }
  },
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
    name: 'Location',
    gs: false,
    id: 'P',
    x: 'O',
    y: ['A'],
    xLabel: 'Longitude [deg]',
    yLabel: 'Latitude [deg]'
  },
  {
    name: 'Altitude',
    gs: true,
    id: 'P',
    x: 't',
    y: ['H'],
    xLabel: 't [ms]',
    yLabel: 'Altitude [m]'
  },
  {
    name: 'Battery',
    gs: false,
    id: 'B',
    x: 't',
    y: ['P', 'C', 'D'],
    xLabel: 't [ms]',
    yLabel: 'Voltage [V]',
    yMin: 0,
    yMax: 15
  },
  {
    name: 'Location',
    gs: true,
    id: 'P',
    x: 'O',
    y: ['A'],
    xLabel: 'Longitude [deg]',
    yLabel: 'Latitude [deg]'
  },
  {
    name: 'Battery',
    gs: true,
    id: 'B',
    x: 't',
    y: ['P', 'C', 'D'],
    xLabel: 't [ms]',
    yLabel: 'Voltage [V]',
    yMin: 0,
    yMax: 10,
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
            radius: 1,
          }
        },
        scales: {
          xAxes: [{
            display: true,
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
            ticks:  {
              min: chart.yMin,
              max: chart.yMax
            },
            scaleLabel: {
              display: true,
              labelString: chart.yLabel
            }}
          ]
        }
      }
    }

    chart.chart = new Chart(canvas, config);
  }
}

function addHistory(command) {

  for (chart of charts) {
    if (chart.id == command.id) {
      const x = command.entries.find(entry => entry.type == chart.x).payload;
      chart.chart.data.labels.push(x.payload);


      chart.chart.data.datasets.forEach((dataset) => {
        const y = command.entries.find(
          entry => entry.type == dataset.entry_type).payload;
        dataset.data.push({x, y});
      })
      chart.chart.update();
    }
  }
}

function main() {
  setInterval(fetch, 1000 / POLLING_FREQ);

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

function fetch() {
  // gs_packets['Sample'].updated = true;

  for (let id in tlm_packets) {
    tlm_packets[id].updated = false;
  }
  for (let id in gs_packets) {
    gs_packets[id].updated = false;
  }

  console.log('fetch', tlm_index, gs_index);

  for (gs of [false, true]) {
    $.ajax({
      url: host + (gs ? '/gs' : '/tlm'),
      type: 'GET',
      data: { index: gs ? gs_index : tlm_index },
      dataType: 'text',
      async: true,
      cache: false,
      timeout: 1000 / POLLING_FREQ}).then((str) => {
        $('#connection-error').hide();

        const lines = str.split('\n').filter(line => line != "");
        if (gs) gs_index += lines.length;
        else tlm_index += lines.length;
        const commands = lines.map(parseCommandHex);

        commands.forEach((command, i) => {
          console.log('command ' + ((gs ? gs_index : tlm_index ) + i), command);
          command.updated = true;
          command.date = new Date();

          addHistory(command);

          if (gs) gs_packets[command.id] = command;
          else tlm_packets[command.id] = command;
        });

        render();
      }).catch((e) => {
        $('#connection-error').show();
        console.error(e);
        render();
      });
  }
}

function render() {
  // $('#rocket-packets').empty();
  // for (let id in rocket_packets) {
  //   $('#rocket-packets').append(commandItem(rocket_packets[id]));
  // }
  $('#tlm-packets').empty();
  for (let id in tlm_packets) {
    $('#tlm-packets').append(commandItem(tlm_packets[id]));
  }
  $('#gs-packets').empty();
  for (let id in gs_packets) {
    $('#gs-packets').append(commandItem(gs_packets[id]));
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

  return `<tr>
            <td>${entry.name} [${entry.unit}]</td>
            <td>${payload}</td>
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

      if (type == 't') {
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

