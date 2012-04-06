function varargout = video_tut(varargin)
% VIDEO_TUT MATLAB code for video_tut.fig
%      VIDEO_TUT, by itself, creates a new VIDEO_TUT or raises the existing
%      singleton*.
%
%      H = VIDEO_TUT returns the handle to a new VIDEO_TUT or the handle to
%      the existing singleton*.
%
%      VIDEO_TUT('CALLBACK',hObject,eventData,handles,...) calls the local
%      function named CALLBACK in VIDEO_TUT.M with the given input arguments.
%
%      VIDEO_TUT('Property','Value',...) creates a new VIDEO_TUT or raises the
%      existing singleton*.  Starting from the left, property value pairs are
%      applied to the GUI before video_tut_OpeningFcn gets called.  An
%      unrecognized property name or invalid value makes property application
%      stop.  All inputs are passed to video_tut_OpeningFcn via varargin.
%
%      *See GUI Options on GUIDE's Tools menu.  Choose "GUI allows only one
%      instance to run (singleton)".
%
% See also: GUIDE, GUIDATA, GUIHANDLES

% Edit the above text to modify the response to help video_tut

% Last Modified by GUIDE v2.5 07-Feb-2011 12:20:05

% Begin initialization code - DO NOT EDIT
gui_Singleton = 1;
gui_State = struct('gui_Name',       mfilename, ...
                   'gui_Singleton',  gui_Singleton, ...
                   'gui_OpeningFcn', @video_tut_OpeningFcn, ...
                   'gui_OutputFcn',  @video_tut_OutputFcn, ...
                   'gui_LayoutFcn',  [] , ...
                   'gui_Callback',   []);
if nargin && ischar(varargin{1})
    gui_State.gui_Callback = str2func(varargin{1});
end

if nargout
    [varargout{1:nargout}] = gui_mainfcn(gui_State, varargin{:});
else
    gui_mainfcn(gui_State, varargin{:});
end
% End initialization code - DO NOT EDIT


% --- Executes just before video_tut is made visible.
function video_tut_OpeningFcn(hObject, eventdata, handles, varargin)
% This function has no output args, see OutputFcn.
% hObject    handle to figure
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
% varargin   command line arguments to video_tut (see VARARGIN)


handles.peaks = peaks(35);

handles.membrane = membrane;

[x,y]=meshgrid(-8:0.5:8);
r=sqrt(x.^2+y.^2)+eps;
sinc=sin(r)./r;
handles.sinc = sinc;

handles.current_data = handles.peaks;
surf(handles.current_data);


% Choose default command line output for video_tut
handles.output = hObject;

% Update handles structure
guidata(hObject, handles);

% UIWAIT makes video_tut wait for user response (see UIRESUME)
% uiwait(handles.figure1);


% --- Outputs from this function are returned to the command line.
function varargout = video_tut_OutputFcn(hObject, eventdata, handles) 
% varargout  cell array for returning output args (see VARARGOUT);
% hObject    handle to figure
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Get default command line output from handles structure
varargout{1} = handles.output;


% --- Executes on selection change in popupmenu.
function popupmenu_Callback(hObject, eventdata, handles)
% hObject    handle to popupmenu (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: contents = cellstr(get(hObject,'String')) returns popupmenu contents as cell array
%        contents{get(hObject,'Value')} returns selected item from popupmenu
val = get(hObject, 'Value');
str = get(hObject, 'String');

switch str{val}
    case 'peaks'
        handles.current_data = handles.peaks;
    case 'membrane'
        handles.current_data = handles.membrane;
    case 'sinc'
        handles.current_data = handles.sinc;
end

guidata(hObject, handles);
    


% --- Executes during object creation, after setting all properties.
function popupmenu_CreateFcn(hObject, eventdata, handles)
% hObject    handle to popupmenu (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: popupmenu controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end


% --- Executes on button press in button_surf.
function button_surf_Callback(hObject, eventdata, handles)
% hObject    handle to button_surf (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

surf(handles.current_data)


% --- Executes on button press in button_mesh.
function button_mesh_Callback(hObject, eventdata, handles)
% hObject    handle to button_mesh (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

mesh(handles.current_data)


% --- Executes on button press in button_contour.
function button_contour_Callback(hObject, eventdata, handles)
% hObject    handle to button_contour (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

contour(handles.current_data)
